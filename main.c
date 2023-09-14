#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "vm.c"

int main(){
	VM* vm = create_vm();

	// th 15
	
	printf("Program Start \n");
	for(int i=0; i<10; i++){
		push_int(vm, i);
		if(rand()%10>5){
			pop(vm);
		}
	}
	printf("Program End \n");
}

