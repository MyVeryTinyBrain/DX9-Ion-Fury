#pragma once

// ==================================================================================================
// 함수를 구현합니다.
// T 타입으로의 형 변환이 가능한지 dynamic_cast를 이용하여 런타임에 검사합니다.
// 단 포인터 연산(GetPointer, operator -> 등)을 하는 경우에는 static_cast를 이용하여 컴파일에 검사합니다.
// 가능하다면 정상적인 Ref<T> 타입을 반환합니다.
// 불가능하다면 nullptr을 포함하는 Ref<T> 타입을 반환합니다.
// ==================================================================================================
#define DefineGetReferenceAs(T)																		\
inline Ref<T> GetReferenceAs##T()																	\
{																									\
	return GetReferenceAs<T>();																		\
}

// ==================================================================================================
// 함수를 구현합니다.
// T 타입으로의 형 변환이 가능한지 검사하지 않습니다.
// 단 포인터 연산(GetPointer, operator -> 등)을 하는 경우에는 static_cast를 이용하여 컴파일에 검사합니다.
// ==================================================================================================
#define DefineGetReferenceTo(T)																		\
inline Ref<T> GetReferenceTo##T()																	\
{																									\
	return GetReferenceTo<T>();																		\
}																									\
__declspec(property(get = GetReferenceTo##T)) Ref<T> ref##T;