#pragma once

template <class T>
inline void SafeDelete(T*& pointer)
{
	if (pointer)
	{
		delete pointer;
		pointer = nullptr;
	}
}

template <class T>
inline void SafeDeleteArray(T*& arrayBegin)
{
	if (arrayBegin)
	{
		delete [] arrayBegin;
		arrayBegin = nullptr;
	}
}

template <class Container, class T>
inline typename Container::iterator FindInContainer(Container& container, const T& target)
{
	return std::find(container.begin(), container.end(), target);
}

template <class Container, class T>
inline typename Container::iterator ContainsInContainer(Container& container, const T& target)
{
	auto find_it = std::find(container.begin(), container.end(), target);
	if (find_it == container.end())
		return false;
	else
		return true;
}
