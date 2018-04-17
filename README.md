# SIMD instructions for Node.js

Historically, processor architectures have allowed only a very limitted set of instructions.  
These instructions, called machine code, allow for simple operations like movement, multiplication and addition of single values.  To perform multiple operations required multiple instructions and thus, multiple clock cycles.

However, modern processor architectures have recently begun to include a new set of vector based instructions, called SIMD.  These instructions allow basic operations to act on small vectors of data. Because of this easy parallelization, the speed boost from using SIMD instructions can be by several factors.

So far the SIMD operation set has only been accessible from Assembly, C and C++. This is an experiment to see if a Javascript API can be created for intrinsic SIMD operations.

## Types API

The API used for this experiment consists of several layers of abstraction.  Instead of presenting a raw interface to the intrinsic types, this module attempts to abstract away some of the frustration of SIMD.

The C++ intrinsic type known as `__m256d` (a 256 bit vector of 4 64 bit double precision floats) is presented to javascript as `Float64x4`. Likewise, `Float32x8` is a 256 bit vector of 8 32 bit single precision floats.


```javascript
var SIMD = require('./simd')

var a = new SIMD.Float64x4(1.0,2.0,3.0,4.0);

a.get(0) => 1.0
a.get(1) => 2.0
a.get(5) => undefined
```
## Arrays API

Of course, you could just ignore those altogether and simply use the SIMD optimized arrays.

 - Float64SIMDArray
 - Float32SIMDArray
 - Int64SIMDArray
 - Int32SIMDArray
 - Int16SIMDArray
 - Int8SIMDArray
 - Uint64SIMDArray
 - Uint32SIMDArray
 - Uint16SIMDArray
 - Uint8SIMDArray

## Functions API

```
mul
add
sub
```
