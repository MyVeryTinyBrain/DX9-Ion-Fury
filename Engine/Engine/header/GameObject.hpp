#pragma once

#include "GameObject.h"
#include "Transform.h"

template<class T>
inline T * GameObject::AddComponent()
{
	T* component = new T;
	component->Initialize(this, transform);
	m_components.push_back(component);
	return component;
}

template<class T>
inline bool GameObject::RemoveComponent()
{
	for (auto it = m_components.begin(); it != m_components.end(); ++it) 
	{
		Component* component = *it;

		// �ı��� ������Ʈ�� Ž������ ���ܵ˴ϴ�.
		if (component->IsShouldDestroy()) 
			continue;

		T* cast = dynamic_cast<T*>(component);
		if (cast) 
		{
			// ���� ������ ����Ʈ������ ���Ŵ� �̰����� ���� �ʽ��ϴ�.
			component->Destroy();
			return true;
		}
	}
	return false;
}

template<class T>
inline T * GameObject::GetComponent()
{
	for (auto& component : m_components) 
	{
		// �ı��� ������Ʈ�� Ž������ ���ܵ˴ϴ�.
		if (component->IsShouldDestroy()) 
			continue;

		T* cast = dynamic_cast<T*>(component);
		if (cast) 
			return cast;
	}
	return nullptr;
}

template<class T>
inline std::vector<T*> GameObject::GetComponents()
{
	std::vector<T*> test;
	for (auto& component : m_components)
	{
		// �ı��� ������Ʈ�� Ž������ ���ܵ˴ϴ�.
		if (component->IsShouldDestroy()) 
			continue;

		T* cast = dynamic_cast<T*>(component);
		if (cast)
			return test.push_back(cast);
	}
	return test;
}

template<class T>
inline T * GameObject::GetComponentInChild()
{
	std::stack<Transform*> s;
	s.push(transform);

	while (!s.empty()) 
	{
		Transform* t = s.top(); s.pop();
		T* component = t->gameObject->GetComponent<T>();
		if (component) 
			return component;

		std::vector<Transform*> v = t->GetChilds();
		for (auto& child : v)
			s.push(child);
	}
	return nullptr;
}

template<class T>
inline std::vector<T*> GameObject::GetComponentsInChild()
{
	std::stack<Transform*> s;
	s.push(transform);

	std::vector<T*> components;
	while (!s.empty())
	{
		Transform* t = s.top(); s.pop();
		T* component = t->gameObject->GetComponent<T>();
		if (component)
			components.push_back(component);

		std::vector<Transform*> v = t->GetChilds();
		for (auto& child : v)
			s.push(child);
	}
	return components;
}
