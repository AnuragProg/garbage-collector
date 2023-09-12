#include <stdio.h>
#include <assert.h>
#include "vm.c"

int main(){
	VM* vm = create_vm();

	// th 15
	
	for(int i=0; i<300; i++){
		push_int(vm, i);
		if(i%5==0){
			pop(vm);
		}
	}
}

