#pragma once

class ObjectRat : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Start);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(OnDestroy);

private:

	Vec3 ToSlopeVelocity(const Vec3& velocity, float rayLength = FLT_MAX) const;

	float AngleToPlayer() const;

	float AngleToPlayerWithSign() const;

	void SetTargetXZCoord(const Vec3& point);

private:

	UserMeshRenderer* m_debugRenderer = nullptr;

	QuadUserMesh* m_quad = nullptr;

	class ObjectRatAnimator* m_animator = nullptr;

	float m_radius = 0.5f;

	Vec3 m_initCoord;

	Vec3 m_targetXZCoord;

	bool m_hasTargetCoord = false;

	float m_breakTime = 0;

	float m_moveDist = 2.0f;

	float m_speed = 1.0f;

	float m_runFactor = 3.0f;

	bool m_run = false;
};

