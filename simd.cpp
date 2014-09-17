
/**
 *
 * SIMD objects for Node.js
 *
 */

#ifndef BUILDING_NODE_EXTENSION
	#define BUILDING_NODE_EXTENSION
#endif

#include "arraywrappers.h"
 #include "typewrappers.h"

#include <v8.h>
#include <node.h>

using namespace v8;

void init( Handle<Object> exports, Handle<Object> module ) 
{
	// types
	Float64x4::Export(exports,"Float64x4");
	Float32x8::Export(exports,"Float32x8");

	// float arrays
	Float64SIMDArray::Export(exports,"Float64SIMDArray");
	// Float32SIMDArray::Export(exports);
	
	// integer arrays
	// Int64SIMDArray::Export(exports);
	Int32SIMDArray::Export(exports,"Int32SIMDArray");
	// Int16SIMDArray::Export(exports);
	// Int8SIMDArray::Export(exports);
	// Uint64SIMDArray::Export(exports);
	// Uint32SIMDArray::Export(exports);
	// Uint16SIMDArray::Export(exports);
	// Uint8SIMDArray::Export(exports);

}

NODE_MODULE( simd, init )