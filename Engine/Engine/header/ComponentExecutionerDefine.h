#pragma once

#define TryAddToExecutionTarget(Component, FlagName)												\
if (Component->ComponentCallFlag(FlagName))															\
{																									\
	ComponentCallFlag(FlagName).push_back(Component);												\
}

#define TryAddToExecutionTargetAndSetFalse(Component, FlagName)										\
if (Component->ComponentCallFlag(FlagName))															\
{																									\
	ComponentCallFlag(FlagName).push_back(Component);												\
	Component->ComponentCallFlag(FlagName) = false;													\
}

#define SortByExecutionOrder(FlagName)																\
std::sort(																							\
	ComponentCallFlag(FlagName).begin(),															\
	ComponentCallFlag(FlagName).end(),																\
	[](Component* lhs, Component* rhs)																\
{																									\
	return lhs->ComponentCallFlag(FlagName) < rhs->ComponentCallFlag(FlagName);						\
});

#define ExecuteByOrder(Name)																		\
for (auto& component : ComponentCallFlag(Name))														\
{																									\
	if (!component->isWake)																			\
		continue;																					\
	component->Name();																				\
}