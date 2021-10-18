#pragma once

class RigibdoyInterpolateBase
{
public:

	RigibdoyInterpolateBase(class Rigidbody* body);

	virtual ~RigibdoyInterpolateBase() = default;

	// ������ ��Ȱ��ȭ���¿��� Ȱ��ȭ���·� ��ȯ�� �� ȣ���մϴ�.
	virtual void Enable() = 0;

	// ���� �ùķ��̼��� ���� �Ŀ� ȣ���մϴ�.
	// ��ü�� ��� �����մϴ�.
	virtual void BackupPose() = 0;

	// ���� �ùķ��̼��� �����ϱ� ���� ȣ���մϴ�.
	// ��ü�� ��� �����մϴ�.
	virtual void RollbackPose() = 0;

	// ������Ʈ���� ȣ���մϴ�.
	// ���ӿ�����Ʈ�� ��� �����մϴ�.
	virtual void InterpolatePose() = 0;

	// ������Ʈ üũ���� ȣ���մϴ�.
	// ���� �߿� ��ġ�� ����Ǿ��� ��쿡 ����� ��� �����մϴ�.
	virtual void CheckPoseChange() = 0;

public:

	bool IsInterpolatePosition() const;

	bool IsInterpolateRotation() const;

	void SetInterpolatePositionMode(bool value);

	void SetInterpolateRotationMode(bool value);

protected:

	virtual Vec3 CalcInterpolatePosition() const = 0;

	virtual Quat CalcInterpolateRotation() const = 0;

protected:

	class Rigidbody* m_body = nullptr;

	bool m_interpolatePoisiton = true;

	bool m_interpolateRotation = false;
};

