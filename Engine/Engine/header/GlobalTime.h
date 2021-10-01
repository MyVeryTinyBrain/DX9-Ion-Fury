#pragma once

namespace Time
{
	void SetTimeScale(float timeScale);

	void SetFixedTimeScale(float timeScale);

	float TimeScale();

	float FixedTimeScale();
	
	float DeltaTime();
	
	float FixedDeltaTime();
	
	float UnscaledDelteTime();
	
	float UnscaledFixedDeltaTime();
};

