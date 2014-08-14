/*

	VIRTUE

	compile with -O3 on GCC to trigger vectorization and -ftree-vect-loop-version


	TODO -ffast-math -funroll-all-loops -march=corei5


*/


#ifndef VIRTUE_H
#define VIRTUE_H

	#include <stdlib.h>
	#include <stdio.h>
	#include <stdalign.h>
	#include <iostream>


	/**

		Fix a few differences between Visual Studio and GCC for
		things like __declspec and __attribute__

	*/
	#ifdef _MSCV_VER_

		/* MSVC's version of importing the instrinsic functions */
		#include <intrin.h>
		#pragma intrinsic ( _mm_hadd_pd )

		#define ALIGN(n) __declspec(align((n)))

		#define aligned_malloc(ptr,align,size) ptr = _aligned_malloc((size),(align))

	#else

		/* GCC's version of importing the instrinsic functions */
		#include <x86intrin.h>

		#define ALIGN(n) __attribute__((aligned ((n))))

		#define aligned_malloc(ptr,align,size) posix_memalign((void**)&(ptr),(align), (size))

		/*

			GCC uses the __restrict__ keyword instead of 'restrict' since it isn't part of the 
			C++ standard yet.  But we like pretty code.

		*/
		#define restrict __restrict__

	#endif


#endif