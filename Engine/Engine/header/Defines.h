#pragma once

#define SafeDeleteInline(ptr)																		\
if(ptr)																								\
{																									\
	delete ptr;																						\
	ptr = nullptr;																					\
}

#define SafeDeleteArrayInline(arr)																	\
if(arr)																								\
{																									\
	delete [] arr;																					\
	arr = nullptr;																					\
}

#define DeclareSingletone(Name)																		\
private:																							\
static Name g_instance;																				\
public:																								\
static Name* GetInstance();																			\
private:

#define ImplementSingletone(Name)																	\
Name Name::g_instance;																				\
Name* Name::GetInstance()																			\
{																									\
	return &g_instance;																				\
}

#define MsgBox(Caption, Text)																		\
MessageBox(NULL, Text, Caption, MB_OK)

#define DeclareStaticComponent(Name)																\
private:																							\
	static Name* g_instance;																		\
public:																								\
	static Name* GetInstance();																		\
private:


#define ImplementStaticComponent(Name)																\
Name* Name::g_instance = nullptr;																	\
Name* Name::GetInstance()																			\
{																									\
	return g_instance;																				\
}