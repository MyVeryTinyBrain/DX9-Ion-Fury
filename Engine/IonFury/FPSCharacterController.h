#pragma once

class FPSCamera;
class FPSOrthoCamera;

class FPSCharacterController : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(FixedUpdate);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(OnDestroy);

	void OnCollisionEnter(const CollisionEnter& collision);

	void OnCollisionExit(const CollisionExit& collision);

public:

	Rigidbody* GetRigidbody() const;

	CapsuleCollider* GetCollider() const;

	FPSCamera* GetFPSCamera() const;

	Camera* GetCamera() const;

	__declspec(property(get = GetRigidbody)) Rigidbody* rigidbody;

	__declspec(property(get = GetCollider)) CapsuleCollider* collider;

	__declspec(property(get = GetFPSCamera)) FPSCamera* fpsCamera;

	__declspec(property(get = GetCamera)) Camera* camera;

private:

	Rigidbody* m_body = nullptr;

	GameObject* m_subObj = nullptr;

	GameObject* m_colliderObj = nullptr;

	CapsuleCollider* m_collider = nullptr;

	GameObject* m_cameraObj = nullptr;

	FPSCamera* m_camera = nullptr;

	float m_speed = 5.0f;

	float m_jumpSpeed = 6.0f;

	bool m_hasGround = false;

	Vec3 m_moveDirection;
};

