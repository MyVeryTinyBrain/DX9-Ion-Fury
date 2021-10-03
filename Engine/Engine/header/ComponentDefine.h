#pragma once

#define ComponentOrderName(Name)		m_order##Name

#define ComponentCallFlagName(Name)		m_call##Name

#define ComponentSetCallName(Name)		SetCall##Name

#define ComponentCallFlag(Name)			ComponentCallFlagName(Name)

#define ComponentSetCall(Name)			ComponentSetCallName(Name)()

#define DefineComponentFunction(Name)																\
order_t ComponentOrderName(Name) = 0;																\
bool ComponentCallFlagName(Name) = true;															\
inline order_t Get##Name##Order() { return ComponentOrderName(Name); }								\
inline virtual void ComponentSetCallName(Name)() { ComponentCallFlagName(Name) = false; }			\
virtual void Name() {}																				

#define OverrideComponentFunction(Name)																\
inline virtual void ComponentSetCallName(Name)() {}													\
protected:																							\
virtual void Name() override;
