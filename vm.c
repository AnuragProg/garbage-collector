#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#define STACK_MAX 256
#define INITIAL_GC_THRESHOLD 15

typedef enum {
	OBJ_INT,	
	OBJ_OBJ
} ObjectType;


typedef struct sObject{
	char marked;
	struct sObject* next;// next obj in list for vm to keep track of

	ObjectType type;
	union{
		int value;	

		struct{
			struct sObject* prop1;
			struct sObject* prop2;
		};
	};
}Object;

void print(Object* start){
	while(start){
		if(start->type == OBJ_OBJ){
			printf("Object = (marked)\n");
		}else{
			printf("Integer = %d(marked)\n", start->value);
		}
		start = start->next;
	}
}


typedef struct{
	Object* stack[STACK_MAX];
	int stack_size; // mark purpose
	
	Object* obj_head; // sweep purpose
	
	int num_objects;
	int max_objects;
}VM;


VM* create_vm(){
	VM* vm = malloc(sizeof(VM));
	vm->stack_size=0;
	vm->obj_head = NULL;
	vm->num_objects = 0;
	vm->max_objects = INITIAL_GC_THRESHOLD;
	return vm;
}
void mark(Object* obj){
	if(obj->marked){
		return;
	}
	obj->marked = 1;
	if(obj->type == OBJ_OBJ){
		mark(obj->prop1);
		mark(obj->prop2);
	}
}

void markAll(VM* vm){
	printf("Marking\n");
	for(int i=0; i<vm->stack_size; i++){
		mark(vm->stack[i]);
	}
}

void sweep(VM* vm){
	Object* prev = NULL;
	Object* obj = vm->obj_head;

	printf("Sweeping\n");
	while(obj){
		if(!(obj->marked)){
			Object* temp = obj;

			if(prev){
				prev->next = obj->next;
			}else{
				vm->obj_head = obj->next;
			}
			obj = obj->next;
			vm->num_objects--;

			if(temp->type == OBJ_OBJ){
				printf("Clearing object\n");
			}else{
				printf("Clearing integer %d\n", temp->value);
			}

			free(temp);
		}else{
			obj->marked = 0;
			prev = obj;
			obj = obj->next;
		}
	}
}

void garbage_collect(VM* vm){
	printf("Starting Garbage Collection...\n");
	//printf("Before marking\n");
	//print(vm->obj_head);
	markAll(vm);
	//printf("After marking\n");
	//print(vm->obj_head);
	sweep(vm);
	printf("Garbage Collection Ended...\n");
}

Object* create_obj(VM* vm){
	if(vm->num_objects >= vm->max_objects){
		garbage_collect(vm);
	} 
	Object* obj = malloc(sizeof(Object));
	obj->marked = 0;
	vm->num_objects++;
	return obj;
}

Object* pop(VM* vm){
	assert(vm->stack_size-1>=0);
	if(vm->stack[vm->stack_size-1]->type == OBJ_OBJ){
		printf("Popping object\n");
	}else{
		printf("Popping int = %d\n", vm->stack[vm->stack_size-1]->value);
	}
	return vm->stack[--vm->stack_size];
}

void push(VM* vm, Object* obj){
	assert(vm->stack_size + 1 <= STACK_MAX);

	vm->stack[vm->stack_size++] = obj;
	obj->next = vm->obj_head;
	vm->obj_head = obj;

	if(obj->type == OBJ_OBJ){
		printf("Pushing object\n");
	}else{
		printf("Pushing int = %d\n", obj->value);
	}
}

void push_int(VM* vm, int value){
	Object* obj = create_obj(vm);
	obj->type = OBJ_INT;
	obj->value = value;

	push(vm, obj);
}

void push_obj(VM* vm){
	Object* obj = create_obj(vm);
	obj->type = OBJ_OBJ;
	obj->prop1 = pop(vm);
	obj->prop2 = pop(vm);

	push(vm, obj);
}


