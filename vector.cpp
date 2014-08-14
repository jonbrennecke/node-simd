#include "vector.h"

const size_t __sse_vector::size() const
{
	return this->_size;
}

const size_t __sse_vector::realsize() const
{
	return this->_realsize;
}

/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class vector16
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
*/
vector16::vector16 ( size_t size )
{
	this->_size = size;
	this->_realsize = (size_t)( size%2 ? size+1 : size);
	aligned_malloc(this->elems,16,this->_realsize * sizeof(double));
}

vector16::~vector16()
{
	free(this->elems);
}

double vector16::operator[] ( size_t i ) const
{
	return this->elems[i];
}

double& vector16::operator[] ( size_t i )
{
	return this->elems[i];
}

/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class vector32
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
*/
vector32::vector32 ( size_t size )
{
	this->_size = size;
	div_t d = div(size,4); // calculate quotient and remainder in one step
	this->_realsize = (size_t)( d.quot ? size+d.rem : size);
	aligned_malloc(this->elems,32,this->_realsize * sizeof(double));
}

vector32::~vector32()
{
	free(this->elems);
}

double vector32::operator[] ( size_t i ) const
{
	return this->elems[i];
}

double& vector32::operator[] ( size_t i )
{
	return this->elems[i];
}