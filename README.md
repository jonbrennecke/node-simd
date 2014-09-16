SIMD instructions for Node.js

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




