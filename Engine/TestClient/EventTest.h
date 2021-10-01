#pragma once

class EventTest : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Start);

	OverrideComponentFunction(FixedUpdate);

	OverrideComponentFunction(AnimationUpdate);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(LateUpdate);

	OverrideComponentFunction(BeginRender);

	OverrideComponentFunction(BeforeRender);

	OverrideComponentFunction(Render);

	OverrideComponentFunction(AfterRender);

	OverrideComponentFunction(EndRender);

	OverrideComponentFunction(OnWake);

	OverrideComponentFunction(OnSleep);

	OverrideComponentFunction(OnDestroy);
};

