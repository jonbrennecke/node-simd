#ifndef SIMD_TYPES_H
#define SIMD_TYPES_H

#include "memalign.h"
#include <typeinfo>
#include <vector>
#include <list> 		// for std::initializer_list
#include <algorithm>    // for std::copy

/* 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Overloaded loading functions

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
*/

// extract 8 floats into an __m256 register
__m256 _mm_load(const float* ptr)
{
	return _mm256_load_ps(ptr);
}

// extract 4 doubles into an __m256d register
__m256d _mm_load(const double* ptr)
{
	return _mm256_load_pd(ptr);
}

/* 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

SIMDType

SIMDType is a thin wrapper on top of the intrinsic SIMD register types.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
*/
template <class T, class R>
class SIMDType
{
public:
	SIMDType(){}

	// constructor from an initializer_list
	SIMDType( std::initializer_list<T> list )
	{
		// convert the initializer_list into an alligned block of memory and load it into the register
		T* tmp ALIGN(32);
		ALIGNED_MALLOC(tmp,32,list.size() * sizeof(T));
		std::copy(list.begin(),list.end(),tmp);
		this->register_ = _mm_load(tmp);
		this->length_ = list.size();
	}

	// constructor from a vector
	SIMDType( std::vector<T> vec )
	{
		// convert the vector into an alligned block of memory and load it into the register
		T* tmp ALIGN(32);
		ALIGNED_MALLOC(tmp,32,vec.size() * sizeof(T));
		std::copy(vec.begin(),vec.end(),tmp);
		this->register_ = _mm_load(tmp);
		this->length_ = vec.size();
	}

	// constructor from a vector
	SIMDType( T* arrayptr, size_t size )
	{
		// convert the array into an alligned block of memory and load it into the register
		T* tmp ALIGN(32);
		ALIGNED_MALLOC(tmp,32,size * sizeof(T));
		std::copy(arrayptr,arrayptr + size,tmp);
		this->register_ = _mm_load(tmp);
		this->length_ = size;
	}

	~SIMDType(){}

	size_t length() const
	{
		return this->length_;
	}

	// void set( std::vector<T> vec )
	// {
	// TODO
	// }

	// array operators
	const T operator[] ( size_t i ) const { return this->register_[i]; }
	// const T& operator[] ( size_t i ) { return this->register_[i]; }

private:
	R register_;

	// we're calling this 'length' because of Javascript conventions, 
	// even though the convention in the C++ STL is to 'size' for the 
	// number of elements in a container
	size_t length_; 
};

#endif