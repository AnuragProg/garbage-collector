# Garbage Collector

## Overview

This repository contains the source code for a simple garbage collector implemented in C. The garbage collector is designed to manage memory in a virtual machine (VM) environment.

## Features

- **Mark-and-Sweep Algorithm**: The garbage collector employs a basic mark-and-sweep algorithm to identify and collect unreachable objects.

- **Object Types**: The VM supports two types of objects - integers and custom objects with two properties.

- **Dynamic Memory Management**: The collector dynamically manages memory, allocating and deallocating objects as needed.

## File Structure

- **main.c**: Contains the main program that demonstrates the usage of the garbage collector.

- **vm.c**: Implements the virtual machine and garbage collector functionality.

## Usage

To use the garbage collector in your project, follow these steps:

1. Include the `vm.c` file in your project.

2. Create a VM instance using the `create_vm` function.

3. Use the `push_int` and `push_obj` functions to push integers and objects onto the VM stack.

4. Utilize the `pop` function to retrieve values from the stack.

5. The garbage collector will automatically run when the object threshold is reached.

## Example

```c
#include <stdio.h>
#include <stdlib.h>
#include "vm.c"

int main(){
    VM* vm = create_vm();

    printf("Program Start \n");
    for(int i=0; i<10; i++){
        push_int(vm, i);
        if(rand()%10>5){
            pop(vm);
        }
    }
    printf("Program End \n");
}
```

## Building and Execution

1. Compile the program using a C compiler, for example:
    ```bash
    gcc main.c -o main.exe
    ```

2. Run the compiled executable:
    ```bash
    ./main.exe
    ```
