#include "vector.h"

/**
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * create a new Vector of a given type
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * :param size_t size - the number of elements in our vector
 * :param typesize_t elemsize - one of the enumerated types in typesize_t
 *
 * :return vector* - the newly created Vector
 *
 */
extern Vector* createVector( size_t size)
{
	Vector* n = (Vector*)malloc(sizeof(Vector));;
	n->elems = (precision_t*)malloc(size * sizeof(precision_t));
	n->size = size;

	// make sure it worked!
	assert(n->elems);

	return n;
}

/**
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * free the memory allocated to a vector
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * :param vector* - the vector to delete
 *
 */
extern void destroyVector( Vector* n )
{
	free(n->elems);
	free(n);
}

/**
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * get a pointer to a copy of the element at a given index
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * :param vector* a - the vector from which to get an element
 * :param size_t index - index of the value
 *
 * :return void pointer to (a copy of!) the element
 */
extern precision_t* getFromVector( Vector* n, size_t index )
{
	// index must be greater than 0 for obvious reasons
	// assert(index >= 0);

	// precision_t* elem_ptr = malloc(sizeof(precision_t));
	// memcpy(elem_ptr, VECTOR_INDEX(n,index), sizeof(precision_t) );
	// return elem_ptr;
}

/**
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * set the value of the vector at a given index
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * :param size_t index - index of the element to return
 * :param void* value - pointer to the value to set
 *
 */
extern void setToVector( Vector* n, size_t index, precision_t value )
{
	n->elems[index] = value;
	// memcpy( VECTOR_INDEX(n,index), value, sizeof(precision_t) );
}


/**
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * increase the size of an vector
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * :param vector* a - the vector to modify
 * :param size_t newsize - the new size of the vector
 *
 */
extern void resizeVector( Vector* n, size_t newsize )
{
	n->elems = (precision_t*)realloc(n->elems, newsize * sizeof(precision_t));
	assert(n->elems);
	n->size = newsize;
}


/**
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * variadic function to simulate C++ style initializer lists
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * NOTE: if nargs is greater than the size of the vector, then only the first 'n->size'
 * variadic args are selected.
 * 
 * :param vector* n - the vector in which to place the elements
 * :param size_t nargs - number of elements
 * :param ... - variadic arguments that will be casted into whatever type the vector contains
 *
 */
// extern void initVectorFromVarargs( Vector* n, size_t nargs, ... )
// {
// 	va_list argv;
// 	va_start(argv,nargs);
// 	void* tmp; // temporary pointer to handle immediate operands
// 	for (size_t i = 0; i < (nargs <= n->size ? nargs : n->size); ++i){
// 		tmp = va_arg(argv,void*);
// 		setToVector( n, i, &tmp);
// 	}
// 	va_end(argv);
// }

/**
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * variadic function to simulate C++ style initializer lists
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * NOTE: if nargs is greater than the size of the vector, then only the first 'n->size'
 * variadic args are selected.
 * 
 * :param vector* n - the vector in which to place the elements
 * :param size_t nargs - number of elements
 * :param ... - variadic arguments that will be casted into whatever type the vector contains
 *
 */
// extern void pushToVector ( Vector* v, void* value )
// {
// 	resizeVector(v,v->size+1);
// 	setToVector(v,v->size-1,value);
// }



// void vector_concat( vector* a, vector* b )
// {

// }

