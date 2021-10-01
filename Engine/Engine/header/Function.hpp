#pragma once

#include "Function.h"

template<class Ret, class ...Args>
template<class Class>
inline Function<Ret(Args...)>::Function(void* obj, In_MemFunc<Class, Ret, Args...> mf) :
	m_caller(reinterpret_cast<Caller*>(obj)),
	m_func(reinterpret_cast<MemFunc>(mf))
{
}

template<class Ret, class ...Args>
inline Function<Ret(Args...)>::Function(In_GloFunc gf) :
	m_caller(nullptr),
	m_func(FunctionUtility::ConvertFunction<MemFunc>(gf))
{
}

template<class Ret, class ...Args>
inline Function<Ret(Args...)>::Function(const Function& other) :
	m_caller(other.m_caller),
	m_func(other.m_func)
{
}

template<class Ret, class ...Args>
inline Function<Ret(Args...)>::Function(Function&& other) noexcept :
	m_caller(other.m_caller),
	m_func(other.m_func)
{
	other.m_caller = nullptr;
	other.m_func = nullptr;
}

template<class Ret, class ...Args>
inline Function<Ret(Args...)>& Function<Ret(Args...)>::operator=(const Function& other)
{
	m_caller = other.m_caller;
	m_func = other.m_func;

	return *this;
}

template<class Ret, class ...Args>
inline Function<Ret(Args...)>& Function<Ret(Args...)>::operator=(In_GloFunc gf)
{
	m_caller = nullptr;
	m_func = FunctionUtility::ConvertFunction<MemFunc>(gf);

	return *this;
}

template<class Ret, class ...Args>
inline Function<Ret(Args...)>& Function<Ret(Args...)>::operator=(Function&& other) noexcept
{
	m_caller = other.m_caller;
	m_func = other.m_func;

	other.m_caller = nullptr;
	other.m_func = nullptr;

	return *this;
}

template<class Ret, class ...Args>
inline bool Function<Ret(Args...)>::operator==(const Function& other) const
{
	return m_caller == other.m_caller && m_func == other.m_func;
}

template<class Ret, class ...Args>
inline bool Function<Ret(Args...)>::operator!=(const Function& other) const
{
	return !Function::operator=(other);
}

template<class Ret, class ...Args>
inline Ret Function<Ret(Args...)>::operator()(Args ...args)
{
	return Invoke(args...);
}

template<class Ret, class ...Args>
inline Ret Function<Ret(Args...)>::Invoke(Args ...args)
{
	if (m_caller) return (m_caller->*m_func)(args...);
	else return FunctionUtility::ConvertFunction<GloFunc>(m_func)(args...);
}

template<class Ret, class ...Args>
inline void* Function<Ret(Args...)>::GetObject() const
{
	return m_caller;
}

template<class Ret, class ...Args>
inline void* Function<Ret(Args...)>::GetFunctionAddress() const
{
	return m_func;
}

template<class Ret, class ...Args>
inline bool Function<Ret(Args...)>::IsMemberFunction() const
{
	return m_caller != nullptr;
}

