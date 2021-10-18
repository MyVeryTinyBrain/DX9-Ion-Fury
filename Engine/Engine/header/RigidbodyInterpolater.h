#pragma once

#include "RigibdoyInterpolateBase.h"

class RigidbodyInterpolater : public RigibdoyInterpolateBase
{
public:

	RigidbodyInterpolater(class Rigidbody* body);

	virtual ~RigidbodyInterpolater() = default;

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

	Vec3 m_beforePosition;

	Quat m_beforeRotation;
};

