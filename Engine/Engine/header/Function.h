#pragma once

#pragma pointers_to_members(full_generality, virtual_inheritance)

#include "FunctionConvert.h"

class Caller {};

template <class T>
class Function;

template <class Ret, class... Args>
class Function<Ret(Args...)>
{
public:

	using MemFunc = Ret(Caller::*)(Args...);

	using GloFunc = Ret(*)(Args...);

	template <class Class, class Ret, class... Args>
	using In_MemFunc = Ret(Class::*)(Args...);

	using In_GloFunc = GloFunc;

public:

	template <class Class>
	Function(void* obj, In_MemFunc<Class, Ret, Args...> mf);

	Function(In_GloFunc gf);

	Function(const Function& other);

	Function(Function&& other) noexcept;

	Function& operator = (const Function& other);

	Function& operator = (In_GloFunc gf);

	Function& operator = (Function&& other) noexcept;

	bool operator == (const Function& other) const;

	bool operator != (const Function& other) const;

	Ret operator () (Args ...args);

	Ret Invoke(Args ...args);

	void* GetObject() const;

	void* GetFunctionAddress() const;

	bool IsMemberFunction() const;

private:

	Caller* m_caller;

	MemFunc m_func;
};

#include "Function.hpp"
