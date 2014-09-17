
SIMD instructions for Node.js





Historically, processor architectures have allowed only a very limitted set of instructions.  
These instructions, called machine code, allow for simple operations like movement, multiplication and addition of single values.  To perform multiple operations required multiple instructions and thus, multiple clock cycles.

However, modern processor architectures have recently begun to include a new set of vector based instructions, called SIMD.  These instructions allow basic operations to act on small vectors of data. Because of this easy parallelization, the speed boost from using SIMD instructions can be by several factors.

So far the SIMD operation set has only been accessible from Assembly, C and C++. This is an experiment to see if a Javascript API can be created for intrinsic SIMD operations.


The API used for this experiment consists of several layers of abstraction.

Instead of presenting a raw interface to the intrinsic types, this module attempts to abstract away some of the frustration of SIMD.

The C++ intrinsic type known as __m256d (a 256 bit vector of 4 64 bit double precision floats) is presented to javascript as Float64x4. Likewise, Float32x8 is a 256bit vector of 8 32bit single precision floats.

C++ template classes to abstract away from architecture differences in naming

Even easier, perhaps, 

SIMD Object with the properties:


<!-- 128bit  -->
Float32x4
Float32x2

<!-- 256bit SSE -->
Float64x4
Float32x8
Int32x8
Int64x4


<!-- Arrays -->
Float64SIMDArray
Float32SIMDArray
Int64SIMDArray
Int32SIMDArray
Int16SIMDArray
Int8SIMDArray
Uint64SIMDArray
Uint32SIMDArray
Uint16SIMDArray
Uint8SIMDArray

<!-- Functions -->
mul
add
sub

shuffle


new Float64x4(1,2,3,4);



var reg = new Float64x4();
reg.set()

reg.a
reg.b
reg.c
reg.d




<!-- 

 -->


simd.h
	namespace SIMD

	math.h
		SIMD::mul
		SIMD::dot
		SIMD::sub
		SIMD::add
	array.h
		SIMD::Array
		SIMD::ArrayWrapper
	types.h
		SIMD::Type
		SIMD::TypeWrapper
	memalign.h




