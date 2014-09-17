#ifndef SIMD_ARRAY_H
#define SIMD_ARRAY_H

#include "memalign.h"
#include <stdint.h>
#include <typeinfo>
#include <algorithm> // for std::copy
#include <list> // for std::initializer_list

/* 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

STL container for an SIMD optimized, 32-bit aligned array of template elements

In order to optimize with SIMD instructions, the actual size of the allocated 
space for the vector's elements is rounded up to the nearest multiple of 4.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
*/
template <class T>
class SIMDArray
{
public:

	/**
	 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 * 				Iterators
	 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 *
	 * STL-like iteraters over the array
	 *
	 * :see
	 *	http://stackoverflow.com/questions/8054273/how-to-implement-an-stl-style-iterator-and-avoid-common-pitfalls/8054856#8054856
	 *	https://gist.github.com/jeetsukumaran/307264#file-custom_iterator-cpp-L50
	 *	http://stackoverflow.com/questions/7758580/writing-your-own-stl-container/7759622#7759622
	 */
	class iterator
	{
	public:
		typedef iterator self_type;
		typedef T value_type;
		typedef T& reference;
		typedef T* pointer;
		typedef std::forward_iterator_tag iterator_category;
		typedef int difference_type;

		iterator(pointer ptr) : ptr_(ptr) {}
		~iterator(){}
		
		self_type operator++() { self_type i = *this; ptr_++; return i; }
		self_type operator++( int i ) { ptr_++; return *this; }
		reference operator*() { return *(*ptr_); }
		pointer operator->() { return *ptr_; }
		bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
		bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }

	private:
		pointer ptr_;
	};

	class const_iterator
	{
	public:
		typedef const_iterator self_type;
		typedef T value_type;
		typedef T& reference;
		typedef T* pointer;
		typedef std::forward_iterator_tag iterator_category;
		typedef int difference_type;

		const_iterator(pointer ptr) : ptr_(ptr) {}
		~const_iterator(){}
		
		self_type operator++() { self_type i = *this; ptr_++; return i; }
		self_type operator++( int i ) { ptr_++; return *this; }
		const reference operator*() { return *(*ptr_); }
		const pointer operator->() { return *ptr_; }
		bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
		bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }

	private:
		pointer ptr_;
	};

	iterator begin() { return iterator(this->_elems); }
	iterator end() { return iterator(this->_elems + this->_size); }

	const_iterator begin() const { return const_iterator(this->elems_); }
    const_iterator end() const { return const_iterator(this->elems_ + this->size_); }

	// Create an empty SIMDArray of 'length' elements
	// Also serves as a target constructor for the other constructors
	SIMDArray( size_t length )
	{
		this->_length = length;
		div_t d = div(length,4); // calculate quotient and remainder in one step
		this->_size = (size_t)( d.quot ? length+d.rem : length);
		ALIGNED_MALLOC(this->elems,32,this->_size * sizeof(T));
	}

    // default constructor
	SIMDArray() : SIMDArray(0){}

	// C++11 list initialization constructor
	SIMDArray( std::initializer_list<T> list ) : SIMDArray( (size_t)list.length )
	{
		// initialize the members from the list
		// for (auto it = list.begin(); it != list.end(); ++it)
		// {
			
		// }
	}

	~SIMDArray()
	{
		free(this->elems);
	}

	T operator[] ( size_t i ) const
	{
		return this->elems[i];
	}

	T& operator[] ( size_t i )
	{
		return this->elems[i];
	}

	size_t length() const 
	{
		return this->_length;
	}

	size_t size() const 
	{
		return this->_size;
	}

	/**
	 *
	 * return an new SIMDArray Object
	 *
	 */
	SIMDArray<T> slice( size_t begin, size_t end )
	{
		auto other = new SIMDArray( end - begin );
		std::copy( this->elems + begin, this->elems + end, other.begin() );
		return other;
	}

	T* elems ALIGN(32);

protected:
	size_t _length; // length may be odd or even
	size_t _size; // size will always be even and a multiple of 4
};

#endif


