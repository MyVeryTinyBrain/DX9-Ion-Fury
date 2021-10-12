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

public:

	bool IsInterpolatePosition() const;

	bool IsInterpolateRotation() const;

	void SetInterpolatePositionMode(bool value);

	void SetInterpolateRotationMode(bool value);

private:

	Vec3 CalcInterpolatePosition() const;

	Quat CalcInterpolateRotation() const;

private:

	class Rigidbody* m_body = nullptr;

	Vec3 m_backupPosition;

	Quat m_backupRotation;

	bool m_interpolatePoisiton = true;

	bool m_interpolateRotation = false;
};

