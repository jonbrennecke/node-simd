
#ifndef BUILDING_NODE_EXTENSION
#define BUILDING_NODE_EXTENSION
#endif

#include "arraywrappers.h"

using namespace v8;

/**
 *
 * ~~~~~~~~~~~ Float64SIMDArray ~~~~~~~~~~~
 *
 * specialize SIMDArrayWrap with 64 bit floats 
 *
 */

Persistent<Function> Float64SIMDArray::constructor;

Float64SIMDArray::Float64SIMDArray(size_t length) : SIMDArrayWrap(length){}

void Float64SIMDArray::Export(Handle<Object> exports)
{
	Local<FunctionTemplate> tpl = FunctionTemplate::New(Float64SIMDArray::New);
	tpl->SetClassName(String::NewSymbol("Float64SIMDArray"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	// prototype
	tpl->PrototypeTemplate()->Set(String::NewSymbol("get"),
		FunctionTemplate::New(Float64SIMDArray::Get)->GetFunction());
	tpl->PrototypeTemplate()->Set(String::NewSymbol("set"),
		FunctionTemplate::New(Float64SIMDArray::Set)->GetFunction());
	tpl->PrototypeTemplate()->Set(String::NewSymbol("length"),
		FunctionTemplate::New(Float64SIMDArray::Length)->GetFunction());

	constructor = Persistent<Function>::New(tpl->GetFunction());
	exports->Set(String::NewSymbol("Float64SIMDArray"), constructor);
}

/**
 *
 * ~~~~~~~~~~~ Int32SIMDArray ~~~~~~~~~~~
 *
 * specialize SIMDArrayWrap with 32 bit ints 
 *
 */

Persistent<Function> Int32SIMDArray::constructor;

Int32SIMDArray::Int32SIMDArray(size_t length) : SIMDArrayWrap(length){}

void Int32SIMDArray::Export(Handle<Object> exports)
{
	Local<FunctionTemplate> tpl = FunctionTemplate::New(Int32SIMDArray::New);
	tpl->SetClassName(String::NewSymbol("Int32SIMDArray"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	// prototype
	tpl->PrototypeTemplate()->Set(String::NewSymbol("get"),
		FunctionTemplate::New(Int32SIMDArray::Get)->GetFunction());
	tpl->PrototypeTemplate()->Set(String::NewSymbol("set"),
		FunctionTemplate::New(Int32SIMDArray::Set)->GetFunction());
	tpl->PrototypeTemplate()->Set(String::NewSymbol("length"),
		FunctionTemplate::New(Int32SIMDArray::Length)->GetFunction());

	constructor = Persistent<Function>::New(tpl->GetFunction());
	exports->Set(String::NewSymbol("Int32SIMDArray"), constructor);
}