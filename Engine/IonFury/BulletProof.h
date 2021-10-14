#pragma once

// Quad 를 사용하여 총탄 자국을 나타냅니다.
// 벽면의 normal의 반대 방향을 forward로 지정해 사용합니다.

class BulletProof : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

public:

	void InitializeBulletProof(const Vec3& point, const Vec3& normal);

private:

	void MakeEffectOnce(const Vec3 point);

private:

	enum { BULLETPROOF_SELF_DESTROY_TIME = 30 };

	UserMeshRenderer* m_renderer = nullptr;

	float m_selfDestroyCounter = 0;
};

