/*

	VIRTUE

	compile with -O3 on GCC to trigger vectorization and -ftree-vect-loop-version


	TODO -ffast-math -funroll-all-loops -march=corei5


*/


#ifndef SIMD_MEMALIGN_H
#define SIMD_MEMALIGN_H

	#include <stdalign.h>


	/**

		Fix a few differences between Visual Studio and GCC for
		things like __declspec and __attribute__

	*/
	#ifdef _MSCV_VER_

		/* MSVC's version of importing the instrinsic functions */
		#include <intrin.h>
		#pragma intrinsic ( _mm_hadd_pd )

		#define ALIGN(n) __declspec(align((n)))

		#define ALIGNED_MALLOC(ptr,align,size) ptr = _aligned_malloc((size),(align))

	#else

		/* GCC's version of importing the instrinsic functions */
		#include <x86intrin.h>

		#define ALIGN(n) __attribute__((aligned ((n))))

		#define ALIGNED_MALLOC(ptr,align,size) posix_memalign((void**)&(ptr),(align), (size))

		/*

			GCC uses the __restrict__ keyword instead of 'restrict' since it isn't part of the 
			C++ standard yet.  But we like pretty code.

		*/
		#define restrict __restrict__

	#endif


#endif