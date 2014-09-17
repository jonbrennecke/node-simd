#ifndef SIMD_WRAPPERS
#define SIMD_WRAPPERS

#ifndef BUILDING_NODE_EXTENSION
	#define BUILDING_NODE_EXTENSION
#endif

#include "array.h"
#include <stdint.h>
#include <typeinfo>
#include <v8.h>
#include <node.h>

using namespace v8;

/**
 *
 * ~~~~~~~~~~~ SIMDArrayWrap ~~~~~~~~~~~
 *
 * Wrap SIMDArray for use in V8 and Node.js
 * 
 * This is just an abstract class and shouldn't be instantiated
 *
 */
template <class T>
class SIMDArrayWrap : public node::ObjectWrap, public SIMDArray<T>
{
public:
	SIMDArrayWrap(size_t length) : SIMDArray<T>(length) {}

	static Persistent<Function> constructor;

	static Handle<Value> New(const Arguments& args)
	{
		HandleScope scope;

		// Invoked as constructor: `new MyObject(...)`
		if (args.IsConstructCall()) {
			
			size_t value = (size_t)(args[0]->IsUndefined() ? 0 : args[0]->NumberValue());
			SIMDArrayWrap<T>* obj = new SIMDArrayWrap<T>(value);
			obj->Wrap(args.This());
			return args.This();
		
		// Invoked as plain function `MyObject(...)`, turn into construct call.
		} else {
			const int argc = 1;
			Local<Value> argv[argc] = { args[0] };
			return scope.Close(SIMDArrayWrap<T>::constructor->NewInstance(argc, argv));
		}
	}

	/**
	 *
	 * Export the class to javascript
	 *
	 */
	static void Export(Handle<Object> exports, const char* name)
	{
		Local<FunctionTemplate> tpl = FunctionTemplate::New(SIMDArrayWrap<T>::New);
		tpl->SetClassName(String::NewSymbol(name));
		tpl->InstanceTemplate()->SetInternalFieldCount(1);

		// prototype
		tpl->PrototypeTemplate()->Set(String::NewSymbol("get"),
			FunctionTemplate::New(SIMDArrayWrap<T>::Get)->GetFunction());
		tpl->PrototypeTemplate()->Set(String::NewSymbol("set"),
			FunctionTemplate::New(SIMDArrayWrap<T>::Set)->GetFunction());
		tpl->PrototypeTemplate()->Set(String::NewSymbol("length"),
			FunctionTemplate::New(SIMDArrayWrap<T>::Length)->GetFunction());

		SIMDArrayWrap<T>::constructor = Persistent<Function>::New(tpl->GetFunction());
		exports->Set(String::NewSymbol(name), SIMDArrayWrap<T>::constructor);
	}

	/**
	 *
	 * Return the array value at an index
	 *
	 */
	static Handle<Value> Get(const Arguments& args)
	{
		HandleScope scope;
		size_t index = (size_t)args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
		SIMDArrayWrap<T> *self = node::ObjectWrap::Unwrap<SIMDArrayWrap<T>>(args.This());
		return scope.Close( index < self->length() ? Number::New(self->elems[index]) : Undefined() );
	}

	/**
	 *
	 * Set the array value at an index
	 *
	 */
	static Handle<Value> Set(const Arguments& args)
	{
		HandleScope scope;
		size_t index = (size_t)args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
		T value = (T)args[1]->IsUndefined() ? 0 : args[1]->NumberValue();
		SIMDArrayWrap<T> *self = node::ObjectWrap::Unwrap<SIMDArrayWrap<T>>(args.This());
		self->elems[index] = value;
		return scope.Close( index < self->length() ? Number::New(self->elems[index]) : Undefined() );
	}

	/**
	 *
	 * return the length of the array
	 *
	 */
	static Handle<Value> Length(const Arguments& args)
	{
		HandleScope scope;
		SIMDArrayWrap<T> *self = node::ObjectWrap::Unwrap<SIMDArrayWrap<T>>(args.This());
		return scope.Close( Number::New(self->length()) );
	}
};

// static member declaration
template<class T>
Persistent<Function> SIMDArrayWrap<T>::constructor;


/**
 *
 * specialize SIMDArrayWrap with a few types to export to Javascript
 *
 */
typedef SIMDArrayWrap<double> Float64SIMDArray;
typedef SIMDArrayWrap<int32_t> Int32SIMDArray;
 


#endif