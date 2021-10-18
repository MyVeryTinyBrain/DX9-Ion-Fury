#pragma once

#include "RigibdoyInterpolateBase.h"

class RigidbodyExtrapolater : public RigibdoyInterpolateBase
{
public:

	RigidbodyExtrapolater(class Rigidbody* body);

	~RigidbodyExtrapolater() = default;

	// ������ ��Ȱ��ȭ���¿��� Ȱ��ȭ���·� ��ȯ�� �� ȣ���մϴ�.
	virtual void Enable() override;

	// ���� �ùķ��̼��� ���� �Ŀ� ȣ���մϴ�.
	// ��ü�� ��� �����մϴ�.
	virtual void BackupPose() override;

	// ���� �ùķ��̼��� �����ϱ� ���� ȣ���մϴ�.
	// ��ü�� ��� �����մϴ�.
	virtual void RollbackPose() override;

	// ������Ʈ���� ȣ���մϴ�.
	// ���ӿ�����Ʈ�� ��� �����մϴ�.
	virtual void InterpolatePose() override;

	// ������Ʈ üũ���� ȣ���մϴ�.
	// ���� �߿� ��ġ�� ����Ǿ��� ��쿡 ����� ��� �����մϴ�.
	virtual void CheckPoseChange() override;

private:

	virtual Vec3 CalcInterpolatePosition() const override;

	virtual Quat CalcInterpolateRotation() const override;

private:

	Vec3 m_backupPosition;

	Quat m_backupRotation;
};

