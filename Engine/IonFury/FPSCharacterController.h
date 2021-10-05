#pragma once

class FPSCamera;

class FPSCharacterController : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(FixedUpdate);

	OverrideComponentFunction(Update);

public:

	Rigidbody* GetRigidbody() const;

	CapsuleCollider* GetCollider() const;

	__declspec(property(get = GetRigidbody)) Rigidbody* rigidbody;

	__declspec(property(get = GetCollider)) CapsuleCollider* collider;

private:

	Rigidbody* m_body = nullptr;

	GameObject* m_subObj = nullptr;

	GameObject* m_colliderObj = nullptr;

	CapsuleCollider* m_collider = nullptr;

	GameObject* m_cameraObj = nullptr;

	FPSCamera* m_camera = nullptr;

	float m_speed = 5.0f;

	float m_jumpSpeed = 5.0f;

	bool m_hasGround = false;
};

