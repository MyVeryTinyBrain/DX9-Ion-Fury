#pragma once

#include "RigibdoyInterpolateBase.h"

class RigidbodyExtrapolater : public RigibdoyInterpolateBase
{
public:

	RigidbodyExtrapolater(class Rigidbody* body);

	~RigidbodyExtrapolater() = default;

	// 보간이 비활성화상태에서 활성화상태로 전환될 때 호출합니다.
	virtual void Enable() override;

	// 물리 시뮬레이션이 끝난 후에 호출합니다.
	// 강체의 포즈를 저장합니다.
	virtual void BackupPose() override;

	// 물리 시뮬레이션이 시작하기 전에 호출합니다.
	// 강체의 포즈를 복원합니다.
	virtual void RollbackPose() override;

	// 업데이트에서 호출합니다.
	// 게임오브젝트의 포즈를 보관합니다.
	virtual void InterpolatePose() override;

	// 업데이트 체크에서 호출합니다.
	// 보간 중에 위치가 변경되었을 경우에 저장된 포즈를 수정합니다.
	virtual void CheckPoseChange() override;

private:

	virtual Vec3 CalcInterpolatePosition() const override;

	virtual Quat CalcInterpolateRotation() const override;

private:

	Vec3 m_backupPosition;

	Quat m_backupRotation;
};

