#pragma once

// Quad �� ����Ͽ� ��ź �ڱ��� ��Ÿ���ϴ�.
// ������ normal�� �ݴ� ������ forward�� ������ ����մϴ�.

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

