#pragma once

class RigidbodyInterpolationer
{
public:

	RigidbodyInterpolationer(class Rigidbody* body);

	~RigidbodyInterpolationer() = default;

	// ���� �ùķ��̼��� ���� �Ŀ� ȣ���մϴ�.
	// ��ü�� ��� �����մϴ�.
	void BackupPose();

	// ���� �ùķ��̼��� �����ϱ� ���� ȣ���մϴ�.
	// ��ü�� ��� �����մϴ�.
	void RollbackPose();

	// ������Ʈ���� ȣ���մϴ�.
	// ���ӿ�����Ʈ�� ��� �����մϴ�.
	void InterpolatePose();

	// ������Ʈ üũ���� ȣ���մϴ�.
	// ���� �߿� ��ġ�� ����Ǿ��� ��쿡 ����� ��� �����մϴ�.
	void CheckPoseChange();

private:

	Vec3 CalcInterpolatePosition() const;

	Vec3 CalcInterpolateEulerAngle() const;

private:

	class Rigidbody* m_body = nullptr;

	Vec3 m_backupPosition;

	Vec3 m_backupEulerAngle;
};

