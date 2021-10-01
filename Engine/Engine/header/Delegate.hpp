#pragma once

#include "Delegate.h"

template<class Ret, class ...Args>
inline Delegate<Ret(Args...)>::Delegate(Delegate&& other) noexcept
{
	m_funcs = std::move(other.m_funcs);
}

template<class Ret, class ...Args>
inline Delegate<Ret(Args...)>::~Delegate()
{
	Clear();
}

template<class Ret, class ...Args>
inline Delegate<Ret(Args...)>& Delegate<Ret(Args...)>::operator=(const Delegate& other)
{
	m_funcs = other.m_funcs;

	return *this;
}

template<class Ret, class ...Args>
inline Delegate<Ret(Args...)>& Delegate<Ret(Args...)>::operator=(Delegate&& other)
{
	m_funcs = std::move(other.m_funcs);

	return *this;
}

template<class Ret, class ...Args>
inline Delegate<Ret(Args...)>& Delegate<Ret(Args...)>::operator+=(const Function& function)
{
	Add(function);

	return *this;
}

template<class Ret, class ...Args>
inline Delegate<Ret(Args...)>& Delegate<Ret(Args...)>::operator-=(const Function& function)
{
	Remove(function);

	return *this;
}

template<class Ret, class ...Args>
inline void Delegate<Ret(Args...)>::operator()(Args ...args)
{
	Invoke(args...);
}

template<class Ret, class ...Args>
inline void Delegate<Ret(Args...)>::Add(const Function& function)
{
	auto find_it = std::find(m_funcs.begin(), m_funcs.end(), function);
	if (find_it == m_funcs.end())
		m_funcs.push_back(function);
}

template<class Ret, class ...Args>
inline void Delegate<Ret(Args...)>::Remove(const Function& function)
{
	auto find_it = std::find(m_funcs.begin(), m_funcs.end(), function);
	if (find_it != m_funcs.end()) 
		m_funcs.erase(find_it);
}

template<class Ret, class ...Args>
inline void Delegate<Ret(Args...)>::Clear()
{
	m_funcs.clear();
}

template<class Ret, class ...Args>
inline void Delegate<Ret(Args...)>::Invoke(Args ...args)
{
	for (auto& func : m_funcs)
	{
		func(args...);
	}
}

template<class Ret, class ...Args>
inline unsigned long Delegate<Ret(Args...)>::GetFunctionCount() const
{
	return m_funcs.size();
}

template<class Ret, class ...Args>
inline const Function<Ret(Args...)>& Delegate<Ret(Args...)>::GetFunction(unsigned long index) const
{
	return m_funcs[index];
}

template<class Ret, class ...Args>
inline const Function<Ret(Args...)>& Delegate<Ret(Args...)>::GetFrontFunction() const
{
	return m_funcs.front();
}

template<class Ret, class ...Args>
inline const Function<Ret(Args...)>& Delegate<Ret(Args...)>::GetBackFunction() const
{
	return m_funcs.back();
}

template<class Ret, class ...Args>
inline bool Delegate<Ret(Args...)>::Find(const Function& function, unsigned long* pIndex) const
{
	for (unsigned long i = 0; i < m_funcs.size(); ++i)
	{
		if (m_funcs[i] == function)
		{
			*pIndex = i;
			return true;
		}
	}
	return false;
}
