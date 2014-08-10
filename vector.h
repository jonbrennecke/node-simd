#ifndef VECTOR_H
#define VECTOR_H

#include "virtue.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define VECTOR_INDEX(n,i) ((precision_t*) (n)->elems + (sizeof(precision_t) * (i)))

/**
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * A basic data structure for a dynamically typed and 
 * dynamically sized vector
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
typedef struct
{
	precision_t* elems;
	size_t size;

} Vector;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// functions that act on vectors
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
extern Vector* createVector( size_t );
extern void destroyVector( Vector* );
extern precision_t getFromVector( Vector*, size_t );
extern void setToVector( Vector*, size_t, precision_t );
extern void resizeVector( Vector*, size_t );
// extern void initVectorFromVarargs( Vector*, size_t, ... );
// extern void pushToVector ( Vector*, void* );

#endif