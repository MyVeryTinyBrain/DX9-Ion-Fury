#pragma once

class RigidbodyInterpolationer
{
public:

	RigidbodyInterpolationer(class Rigidbody* body);

	~RigidbodyInterpolationer() = default;

	// 물리 시뮬레이션이 끝난 후에 호출합니다.
	// 강체의 포즈를 저장합니다.
	void BackupPose();

	// 물리 시뮬레이션이 시작하기 전에 호출합니다.
	// 강체의 포즈를 복원합니다.
	void RollbackPose();

	// 업데이트에서 호출합니다.
	// 게임오브젝트의 포즈를 보관합니다.
	void InterpolatePose();

	// 업데이트 체크에서 호출합니다.
	// 보간 중에 위치가 변경되었을 경우에 저장된 포즈를 수정합니다.
	void CheckPoseChange();

private:

	Vec3 CalcInterpolatePosition() const;

	Vec3 CalcInterpolateEulerAngle() const;

private:

	class Rigidbody* m_body = nullptr;

	Vec3 m_backupPosition;

	Vec3 m_backupEulerAngle;
};

