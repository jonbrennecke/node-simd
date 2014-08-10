#ifndef STACK_H
#define STACK_H

#include "virtue.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


// typedef struct Stack
// {

// 	precision_t* top;

// } Stack;

// static inline Stack* createStack (void)
// {
// 	Stack* stack = (Stack*)malloc(sizeof(Stack));
// 	stack->top = malloc( sizeof(precision_t) * STACK_SIZE );
// 	return stack;
// }


/**
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * vector registers of dynamic size
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
typedef struct Register
{

	size_t size;
	precision_t* elements;

} Register;



static inline Register* initRegister( size_t size )
{
	Register* reg = (Register*)malloc(sizeof(Register));
	reg->elements = (precision_t*)malloc(sizeof(precision_t) * size);
	reg->size = size;
	return reg;
}

typedef struct VM
{
	Register* gen[ NUM_GEN_REGISTERS ];
	Register* stack;

} VM;


static inline VM* initVM(void)
{
	VM* vm = (VM*)malloc(sizeof(Register));
	
	// allocate dynamic memory to general purpose registers
	size_t i = NUM_GEN_REGISTERS;
	while ( i-- )
	{
		vm->gen[i] = initRegister(0);
	}

	// allocate static size to stack pointer
	vm->stack = malloc( sizeof(precision_t) * STACK_SIZE );

	return vm;
}



#endif