
#ifndef SIMD_TYPE_WRAPPERS
#define SIMD_TYPE_WRAPPERS

#include "types.h"
#include <typeinfo>
#include <vector>
#include <list>
#include <v8.h>
#include <node.h>

using namespace v8;

/* 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

SIMDTypeWrapper

SIMDTypeWrapper wraps SIMDType as an object that can exported to Node.js

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
*/
template <class T, class R>
class SIMDTypeWrapper : public node::ObjectWrap, public SIMDType<T,R>
{
public:

	SIMDTypeWrapper( std::initializer_list<T> list ) : SIMDType<T,R>( list ){}
	SIMDTypeWrapper( std::vector<T> vec ) : SIMDType<T,R>( vec ){}

	static Persistent<Function> constructor;

	static Handle<Value> New(const Arguments& args)
	{
		HandleScope scope;

		// Invoked as constructor: `new MyObject(...)`
		if (args.IsConstructCall()) {

			std::vector<T> vec;
			for (int i = 0; i < args.Length(); ++i)
			{
				T val = (T)(args[i]->IsUndefined() ? 0 : args[i]->NumberValue());
				vec.push_back(val);
			}

			SIMDTypeWrapper<T,R>* obj = new SIMDTypeWrapper<T,R>(vec);
			obj->Wrap(args.This());
			return args.This();
		
		// Invoked as plain function `MyObject(...)`, turn into construct call.
		} else {
			const int argc = 1;
			Local<Value> argv[argc] = { args[0] };
			return scope.Close(SIMDTypeWrapper<T,R>::constructor->NewInstance(argc, argv));
		}
	}

	/**
	 *
	 * Return the array value at an index
	 *
	 */
	static Handle<Value> Set(const Arguments& args)
	{
		HandleScope scope;
		// size_t index = (size_t)args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
		SIMDTypeWrapper<T> *self = node::ObjectWrap::Unwrap<SIMDTypeWrapper<T>>(args.This());

		
		
		return scope.Close( index < self->length() ? Number::New(self->elems[index]) : Undefined() );
	}


	static void Export(Handle<Object> exports, const char* name)
	{
		Local<FunctionTemplate> tpl = FunctionTemplate::New(SIMDTypeWrapper<T,R>::New);
		tpl->SetClassName(String::NewSymbol(name));
		tpl->InstanceTemplate()->SetInternalFieldCount(1);

		// prototype
		// tpl->PrototypeTemplate()->Set(String::NewSymbol("get"),
		// 	FunctionTemplate::New(SIMDTypeWrapper::Get)->GetFunction());
		// tpl->PrototypeTemplate()->Set(String::NewSymbol("set"),
		// 	FunctionTemplate::New(SIMDTypeWrapper::Set)->GetFunction());
		// tpl->PrototypeTemplate()->Set(String::NewSymbol("length"),
		// 	FunctionTemplate::New(SIMDTypeWrapper::Length)->GetFunction());

		SIMDTypeWrapper<T,R>::constructor = Persistent<Function>::New(tpl->GetFunction());
		exports->Set(String::NewSymbol(name), SIMDTypeWrapper<T,R>::constructor);
	}
};

// static member declaration
template<class T, class R>
Persistent<Function> SIMDTypeWrapper<T,R>::constructor;

/* 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A few specializations of SIMDTypeWrapper are defined for export

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
*/

// 256 bit
typedef SIMDTypeWrapper<double,__m256d> Float64x4;
typedef SIMDTypeWrapper<float,__m256> Float32x8;

#endif