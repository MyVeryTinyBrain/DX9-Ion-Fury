#pragma once

// Get memory address of member function?
// https://stackoverflow.com/questions/8121320/get-memory-address-of-member-function

namespace FunctionUtility
{
	template <class In_Fx>
	inline void* FunctionToVoidPointer(In_Fx fx)
	{
		void* vp = (void*&)fx;
		return vp;
	}

	template <class Out_Fx>
	inline Out_Fx VoidPointerToFunction(void* vp)
	{
		Out_Fx fx = (Out_Fx&)vp;
		return fx;
	}

	template <class Out_Fx, class In_Fx>
	inline Out_Fx ConvertFunction(In_Fx inFx)
	{
		void* vpInFx = FunctionToVoidPointer<In_Fx>(inFx);
		return VoidPointerToFunction<Out_Fx>(vpInFx);
	}
}

