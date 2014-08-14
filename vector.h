#ifndef VECTOR_H
#define VECTOR_H

#include "virtue.h"

/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
base class for aligned vectors of doubles
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
class __sse_vector
{
public:
	const size_t size() const;
	const size_t realsize() const;
protected:
	size_t _size; // size may be odd or even
	size_t _realsize; // realsize will always be even
};

/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
16 bit aligned vector of doubles

In order to optimize with SIMD instructions, the actual size of the allocated 
space for the vector's elements is rounded up to the nearest multiple of 2.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
*/
class vector16 : public __sse_vector
{
public:
	vector16( size_t size );
	~vector16();
	double operator[] ( size_t i ) const;
	double& operator[] ( size_t i );
	double* elems ALIGN(16);
};

/* 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
32 bit aligned vector of doubles

In order to optimize with SIMD instructions, the actual size of the allocated 
space for the vector's elements is rounded up to the nearest multiple of 4.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
*/
class vector32 : public __sse_vector
{
public:
	vector32( size_t size );
	~vector32();
	double operator[] ( size_t i ) const;
	double& operator[] ( size_t i );
	double* elems ALIGN(32);
};

#endif