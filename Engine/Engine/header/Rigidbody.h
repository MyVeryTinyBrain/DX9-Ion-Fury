#pragma once

#include "Component.h"

enum class PhysicsAxis
{
	NONE = 0,
	X = 1 << 0,
	Y = 1 << 1,
	Z = 1 << 2,
	All = X | Y | Z,
};

enum class ForceMode
{
	Impulse = PxForceMode::eIMPULSE,
	Force = PxForceMode::eFORCE,
	Acceleration = PxForceMode::eACCELERATION,
};

class Rigidbody : public Component
{
	friend class Collider;

	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Start);

	OverrideComponentFunction(BeginPhysicsSimulate);

	OverrideComponentFunction(EndPhysicsSimulate);

	OverrideComponentFunction(BeginFixedUpdate);

	OverrideComponentFunction(FixedUpdateCheck);

	OverrideComponentFunction(BeginUpdate);

	OverrideComponentFunction(UpdateCheck);

	OverrideComponentFunction(OnDestroy);

public:

	bool UseGravity() const;

	void SetUseGravity(bool value);

	bool IsKinematic() const;

	void SetKinematic(bool value);

	bool IsContinousDetection() const;

	void SetContinuousDetection(bool value);

	__declspec(property(get = UseGravity, put = SetUseGravity)) bool useGravity;

	__declspec(property(get = IsKinematic, put = SetKinematic)) bool isKinematic;

	__declspec(property(get = IsContinousDetection, put = SetContinuousDetection)) bool isContinousDetection;

public:

	void ApplyBodyTransformFromGameObject();

	void ApplyGameObjectTransfromFromBody();

	void SetPosition(const Vec3& position);

	void SetRotation(const Quat& rotation);

	void SetEulerAngle(const Vec3& eulerAngle);

public:

	void UpdateMassAndInertia();

	bool IsRigidbodySleep() const;

	void SetRigidbodySleep(bool value);

	float GetSleepThresholder() const;

	void SetSleepThresholder(float value);

	bool IsInterpolateMode() const;

	void SetInterpolate(bool value);

	// 보간이 활성화 되었을 때 위치를 보간하는지에 대한 플래그입니다.
	bool IsInterpolatePosition() const;

	// 보간이 활성화 되었을 때 위치를 보간하는지에 대한 플래그를 설정합니다.
	void SetInterpolatePosition(bool value);

	// 보간이 활성화 되었을 때 회전을 보간하는지에 대한 플래그입니다.
	bool IsInterpolateRotation() const;

	// 보간이 활성화 되었을 때 회전을 보간하는지에 대한 플래그를 설정합니다.
	void SetInterpolateRotation(bool value);

	float GetMass() const;

	void SetMass(float value);

	void SetLinearDamping(float value);

	float GetLinearDamping() const;

	void SetAngularDamping(float value);

	float GetAngularDamping() const;

	Vec3 GetVelocity() const;

	void SetVelocity(const Vec3& velocity);

	void AddForce(const Vec3& force, ForceMode forceMode);

	Vec3 GetAngularVelocity() const;

	void SetAngularVelocity(const Vec3& angularVelocity);

	void SetRotationLockAxis(PhysicsAxis axes, bool value);

	bool GetRotationLockAxis(PhysicsAxis axes) const;

	void SetTranslationLockAxis(PhysicsAxis axes, bool value);

	bool GetTranslationLockAxis(PhysicsAxis axes) const;

	void SetPositionIteration(uint8_t count);

	uint8_t GetPositionIteration() const;

	void SetVelocityIteration(uint8_t count);

	uint8_t GetVelocityIteration() const;

	__declspec(property(get = IsRigidbodySleep, put = SetRigidbodySleep)) bool rigidbodySleep;

	__declspec(property(get = GetSleepThresholder, put = SetSleepThresholder)) float sleepThresholder;

	__declspec(property(get = IsInterpolateMode, put = SetInterpolate)) bool interpolate;

	__declspec(property(get = GetMass, put = SetMass)) float mass;

	__declspec(property(get = GetLinearDamping, put = SetLinearDamping)) float linearDamping;

	__declspec(property(get = GetAngularDamping, put = SetAngularDamping)) float angularDamping;

	__declspec(property(get = GetVelocity, put = SetVelocity)) Vec3 velocity;

	__declspec(property(get = GetAngularVelocity, put = SetAngularVelocity)) Vec3 angularVelocity;

	__declspec(property(get = GetPositionIteration, put = SetPositionIteration)) uint8_t positionIteration;

	__declspec(property(get = GetVelocityIteration, put = SetVelocityIteration)) uint8_t velocityIteration;

public:

	void AttachAll();

	void DetachAll();

private:

	void Attach(class Collider* collider);

	void Detach(class Collider* collider);

	void ApplyFlags();

private:

	PxRigidDynamic* m_body;

	bool m_continous = false;

	class RigidbodyInterpolationer* m_interpolationer = nullptr;

	bool m_interpolate = false;
};

