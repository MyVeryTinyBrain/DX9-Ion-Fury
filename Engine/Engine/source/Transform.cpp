#include "EngineBase.h"
#include "Transform.h"
#include "GameObject.h"

void Transform::SetActiveSelf(bool active)
{
	if (m_activeSelf == active) return;

	m_activeSelf = active;

	OnEnableChanged();

	UpdateActiveInTree();
}

bool Transform::IsActiveSelf() const
{
	return m_activeSelf;
}

bool Transform::IsActiveInTree() const
{
	return m_activeSelf && m_activeInTree;
}

void Transform::SetParent(Transform* parent)
{
	// �� Ʈ�������� �θ�� �η��� ��� �����մϴ�.
	if (parent == this) return;

	// �켱, �θ𿡼� Ż���մϴ�.
	DetachFromParent();

	if (parent)
	{
		// ��ϵǷ��� �θ� �ִٸ�
		// ���ο� �θ��� �ڽ����� ����մϴ�.
		parent->AddChild(this);
	}
}

void Transform::DetachFromParent()
{
	if (!m_parent) return;

	// �θ� �ִٸ� �θ𿡰Լ� Ż���մϴ�.
	m_parent->RemoveChild(this);
}

void Transform::AddChild(Transform* child)
{
	// �� Ʈ�������� �ڽ����� �η��� ��� �����մϴ�.
	if (child == this) return;

	if (!child) return;

	// ===============================================================
	// Ư���� ��쿡 �θ�κ��� Ż���մϴ�.
	// �� �ڵ尡 ������ ���� ��ȯ�� ���� �� �ֽ��ϴ�.
	// A-->B-->C (ȭ��ǥ�� �ڽ��� ��Ÿ���ϴ�.) �� ���� ���谡 ���� ��
	// A �� C �� �ڽ��� �Ǵ� ��쿡�� A-->B-->C-->A-->... �� ����
	// ���� ��ȯ�� ����ϴ�.
	// �̸� �����ϱ� ���ؼ�
	// Ʈ���� �θ�鿡�� ���ڷ� ���� child Ʈ�������� �θ�� �����Ѵٸ�
	// ���ڷ� ���� child Ʈ�������� ���ڷ� ���� child Ʈ�������� 
	// �ڽ� �� �ϳ��� ���� ��� it_prevParent�� �ڽĿ��� �����մϴ�.
	// ���� C-->A-->B ���谡 �ǰ�, ���� ��ȯ�� �����ϴ�.
	// 1. A-->B-->C
	// 2. A-->B   C
	// 3.         C-->A-->B
	// ===============================================================
	Transform* it_prevParent = this;
	Transform* it_parent = m_parent;
	while (it_parent)
	{
		if (it_parent == child)
		{
			it_parent->RemoveChild(it_prevParent);
			break;
		}
		it_prevParent = it_parent;
		it_parent = it_parent->parent;
	}

	// child Ʈ���������� �θ�κ��� Ż���ŵ�ϴ�. 
	child->DetachFromParent();

	// �߰��Ƿ��� child Ʈ�������� �θ� �� Ʈ���������� �����մϴ�.
	child->m_parent = this;

	// �� Ʈ�������� �ڽĿ� �߰��Ƿ��� child Ʈ�������� �߰��մϴ�.
	m_childs.push_back(child);

	// �ڽ����� �߰��� child Ʈ�������� ������Ʈ�մϴ�.

	child->UpdateLocalTransform(UpdateTransformArgument::None);

	child->UpdateActiveInTree();

}

void Transform::RemoveChild(Transform* child)
{
	if (!child) return;

	// child Ʈ�������� �ڽ����� �������� �ʴ´ٸ� �����մϴ�.

	auto find_it = FindInContainer(m_childs, child);

	if (find_it == m_childs.end()) return;

	// child Ʈ�������� �ڽ� ���Ϳ��� �����մϴ�.
	m_childs.erase(find_it);

	// child Ʈ�������� �θ� �������� �����մϴ�.
	child->m_parent = nullptr;

	// �θ𿡼� Ż��� child Ʈ�������� ������Ʈ�մϴ�.

	child->UpdateLocalTransform(UpdateTransformArgument::None);

	child->UpdateActiveInTree();
}

Transform* Transform::GetRoot() const
{
	const Transform* t = this;

	while (t->parent)
	{
		t = t->parent;
	}

	return const_cast<Transform*>(t);
}

Transform* Transform::GetParent() const
{
	return m_parent;
}

size_t Transform::GetChildCount() const
{
	return m_childs.size();
}

Transform* Transform::GetChild(index_t index) const
{
	return m_childs[index];
}

std::vector<Transform*> Transform::GetChilds() const
{
	return m_childs;
}

void Transform::SetPosition(const Vec3& position)
{
	m_position = position;

	UpdateLocalTransform(UpdateTransformArgument::None);
	UpdateChildWorldTransforms(UpdateTransformArgument::None);
}

void Transform::SetRotation(const Quat& rotation)
{
	m_rotation = rotation;
	m_eulerAngle = m_rotation.ToEuler();

	UpdateLocalTransform(UpdateTransformArgument::None);
	UpdateChildWorldTransforms(UpdateTransformArgument::None);
}

void Transform::SetEulerAngle(const Vec3& eulerAngle)
{
	//Vec3 currentEulerAngle = GetEulerAngle();

	//float x = MathEx::DeltaAngle(currentEulerAngle.x, eulerAngle.x);
	//float y = MathEx::DeltaAngle(currentEulerAngle.y, eulerAngle.y);
	//float z = MathEx::DeltaAngle(currentEulerAngle.z, eulerAngle.z);

	//m_rotation = Quat::FromEuler(x, y, z) * m_rotation;

	m_rotation = Quat::FromEuler(eulerAngle.x, eulerAngle.y, eulerAngle.z);
	m_eulerAngle = eulerAngle;

	UpdateLocalTransform(UpdateTransformArgument::FromEulerAngle);
	UpdateChildWorldTransforms(UpdateTransformArgument::FromEulerAngle);
}

void Transform::SetScale(const Vec3& scale)
{
	m_scale = scale;

	UpdateLocalTransform(UpdateTransformArgument::None);
	UpdateChildWorldTransforms(UpdateTransformArgument::None);
}

void Transform::SetLocalPosition(const Vec3& localPosition)
{
	m_localPosition = localPosition;

	UpdateWorldPosition(UpdateTransformArgument::None);
	UpdateChildWorldTransforms(UpdateTransformArgument::None);
}

void Transform::SetLocalRotation(const Quat& localRotation)
{
	m_localRotation = localRotation;
	m_localEulerAngle = m_localRotation.ToEuler();

	UpdateWorldRotation(UpdateTransformArgument::None);
	UpdateChildWorldTransforms(UpdateTransformArgument::None);
}

void Transform::SetLocalEulerAngle(const Vec3& localEulerAngle)
{
	m_localRotation = Quat::FromEuler(localEulerAngle.x, localEulerAngle.y, localEulerAngle.z);
	m_localEulerAngle = localEulerAngle;

	UpdateWorldRotation(UpdateTransformArgument::FromEulerAngle);
	UpdateChildWorldTransforms(UpdateTransformArgument::FromEulerAngle);
}

void Transform::SetLocalScale(const Vec3& localScale)
{
	m_localScale = localScale;

	UpdateWorldScale(UpdateTransformArgument::None);
	UpdateChildWorldTransforms(UpdateTransformArgument::None);
}

const Vec3& Transform::GetPosition() const
{
	return m_position;
}

const Quat& Transform::GetRotation() const
{
	return m_rotation;
}

Vec3 Transform::GetEulerAngle() const
{
	//return m_rotation.ToEuler();
	return m_eulerAngle;
}

const Vec3& Transform::GetScale() const
{
	return m_scale;
}

const Vec3& Transform::GetLocalPosition() const
{
	return m_localPosition;
}

const Quat& Transform::GetLocalRotation() const
{
	return m_localRotation;
}

Vec3 Transform::GetLocalEulerAngle() const
{
	//return m_localRotation.ToEuler();
	return m_localEulerAngle;
}

const Vec3& Transform::GetLocalScale() const
{
	return m_localScale;
}

Mat4 Transform::GetLocalToWorldMatrix() const
{
	return Mat4::SRT(m_scale, m_rotation.ToEuler() * Deg2Rad, m_position);
}

Mat4 Transform::GetWorldToLocalMatrix() const
{
	Vec3 invPosition = -m_position;
	Vec3 invEulerAngle = m_rotation.inversed().ToEuler();
	Vec3 invScale = Vec3(1.0f / m_scale.x, 1.0f / m_scale.y, 1.0f / m_scale.z);
	return Mat4::TRS(invPosition, invEulerAngle * Deg2Rad, invScale);
}

void Transform::SetRightDirection(const Vec3& right)
{
	Vec3 x = right.normalized();

	if (x.sqrMagnitude() == 0)
	{
		x = Vec3::right();
	}

	SetRotation(Quat::FromToRotation(Vec3::right(), x));
	//Vec3 rotatedEulerAngle = Quat::FromToRotation(Vec3::right(), x).ToEuler();
	//eulerAngle = rotatedEulerAngle;
}

void Transform::SetUpDirection(const Vec3& up)
{
	Vec3 y = up.normalized();

	if (y.sqrMagnitude() == 0)
	{
		y = Vec3::up();
	}

	SetRotation(Quat::FromToRotation(Vec3::up(), y));
	//Vec3 rotatedEulerAngle = Quat::FromToRotation(Vec3::up(), y).ToEuler();
	//eulerAngle = rotatedEulerAngle;
}

void Transform::SetForwardDirection(const Vec3& forward)
{
	Vec3 z = forward.normalized();

	if (z.sqrMagnitude() == 0)
	{
		z = Vec3::right();
	}

	SetRotation(Quat::LookRotation(z, Vec3::up()));
	//Vec3 rotatedEulerAngle = Quat::FromToRotation(Vec3::forawrd(), z).ToEuler();
	//eulerAngle = rotatedEulerAngle;
}

Vec3 Transform::GetRightDirection() const
{
	//return localToWorld.MultiplyVector(Vec3::right());
	
	Vec3 right = localToWorld.GetRow(0);
	return right.normalized();
}

Vec3 Transform::GetUpDirection() const
{
	//return localToWorld.MultiplyVector(Vec3::up());
	
	Vec3 up = localToWorld.GetRow(1);
	return up.normalized();
}

Vec3 Transform::GetForwardDirection() const
{
	//return localToWorld.MultiplyVector(Vec3::forawrd());

	Vec3 forward = localToWorld.GetRow(2);
	return forward.normalized();
}

void Transform::UpdateActiveInTree()
{
	// ����Ǳ� ���� Ʈ���� Ȱ��ȭ ���¸� ����մϴ�.
	bool beforeActiveInTree = m_activeInTree;

	if (!m_parent)
	{
		// �θ� ���ٸ� Ʈ���� �ֻ���̹Ƿ� ���� Ʈ�������� ������ ���� �ʽ��ϴ�.
		// �� ���� Ʈ���� Ȱ��ȭ ���´� ������ ���Դϴ�.
		m_activeInTree = true;
	}
	else
	{
		// �θ� �ִ� ��쿡��
		// �θ� Ȱ��ȭ �Ǿ��־�� �ϸ�, �θ��� Ʈ���� Ȱ��ȭ ���µ� ���̾�� �մϴ�.
		m_activeInTree = m_parent->m_activeInTree && m_parent->m_activeSelf;
	}

	if (m_activeInTree != beforeActiveInTree)
	{
		// Ʈ���� Ȱ��ȭ ���°� ����Ǿ��ٸ� isWake �÷��׸� �缳���ϱ� ���� �� �Լ��� ȣ���մϴ�.
		OnEnableChanged();
	}

	for (auto child : m_childs)
	{
		// �ڽĵ��� Ʈ���� Ȱ��ȭ ���¸� �缳���մϴ�.
		child->UpdateActiveInTree();
	}
}

void Transform::UpdateChildWorldTransforms(const UpdateTransformArgument& args)
{
	for (auto child : m_childs)
	{
		child->UpdateWorldTransform(args);
		child->UpdateChildWorldTransforms(args);
	}
}

void Transform::UpdateLocalTransform(const UpdateTransformArgument& args)
{
	UpdateLocalPosition(args);
	UpdateLocalRotation(args);
	UpdateLocalScale(args);
}

void Transform::UpdateWorldTransform(const UpdateTransformArgument& args)
{
	UpdateWorldPosition(args);
	UpdateWorldRotation(args);
	UpdateWorldScale(args);
}

void Transform::UpdateLocalPosition(const UpdateTransformArgument& args)
{
	if (m_parent)
		m_localPosition = m_parent->worldToLocal.MultiplyPoint(m_position);
	else
		m_localPosition = m_position;
}

void Transform::UpdateLocalRotation(const UpdateTransformArgument& args)
{
	if (m_parent)
		m_localRotation = m_parent->m_rotation.inversed() * m_rotation;
	else
		m_localRotation = m_rotation;

	if (unsigned int(args) & unsigned int(UpdateTransformArgument::FromEulerAngle))
	{
		if (m_parent)
			m_localEulerAngle = m_eulerAngle - m_parent->m_eulerAngle;
		else
			m_localEulerAngle = m_eulerAngle;
	}
	else
	{
		m_localEulerAngle = m_localRotation.ToEuler();
	}
}

void Transform::UpdateLocalScale(const UpdateTransformArgument& args)
{
	if (m_parent)
	{
		m_localScale = Vec3(
			m_scale.x / m_parent->m_scale.x,
			m_scale.y / m_parent->m_scale.y,
			m_scale.z / m_parent->m_scale.z);
	}
	else
	{
		m_localScale = m_scale;
	}
}

void Transform::UpdateWorldPosition(const UpdateTransformArgument& args)
{
	if (m_parent)
		m_position = m_parent->localToWorld.MultiplyPoint(m_localPosition);
	else
		m_position = m_localPosition;
}

void Transform::UpdateWorldRotation(const UpdateTransformArgument& args)
{
	if (m_parent)
		m_rotation = m_parent->m_rotation * m_localRotation;
	else
		m_rotation = m_localRotation;

	if (unsigned int(args) & unsigned int(UpdateTransformArgument::FromEulerAngle))
	{
		if (m_parent)
			m_eulerAngle = m_localEulerAngle + m_parent->m_eulerAngle;
		else
			m_eulerAngle = m_localEulerAngle;
	}
	else
	{
		m_eulerAngle = m_rotation.ToEuler();
	}
}

void Transform::UpdateWorldScale(const UpdateTransformArgument& args)
{
	if (m_parent)
	{
		m_scale = Vec3(
			m_localScale.x * m_parent->m_scale.x, 
			m_localScale.y * m_parent->m_scale.y,
			m_localScale.z * m_parent->m_scale.z);
	}
	else
	{
		m_scale = m_localScale;
	}
}

void Transform::OnDestroy()
{
	// ===================================================================================================
	// �� Ʈ�������� �ı��Ǵ� ��쿡��
	// �θ𿡼� Ż��Ǿ�� �ϸ�
	// �ڽĵ� ���� ��� ����� �մϴ�.
	// �̶� �ڽĵ��� ��ȸ�ϸ� �ı� �Լ��� ȣ���� �־�� �ϴµ�
	// �ڽ� Ʈ�������� �θ𿡼� Ż���ϴ� �۾��� �����ϰ� �˴ϴ�.
	// �� �۾��� ��ġ�� ������ �����̳ʸ� ��ȸ�ϸ� ���ÿ� �����̳ʿ��� �����ϴ� ���� ������ �߻��� �� �ֽ��ϴ�.
	// ===================================================================================================

	// Method 1
	// �θ𿡰Լ� Ż���� ��
	// ������ �� ���� �ڽĺ��� �ϳ��� �����մϴ�.
	// �̶� Destroy �Լ� ȣ��� �θ� ���Ϳ��� ���ŵǹǷ�
	// child->Destroy() �Լ��� ȣ���ϴ� �� �����ε� ���Ϳ��� ���ŵ˴ϴ�.

	DetachFromParent();
	gameObject->Destroy();
	while (!m_childs.empty())
	{
		auto child = m_childs.back();
		child->Destroy();
	}

	// Method 2
	// �ڽ��� �����صΰ� ��ȸ�ϸ� �ı��ϴ� ����Դϴ�.
	
	// Transform** childs = new Transform * [m_childs.size()];
	// std::copy(m_childs.begin(), m_childs.end(), childs);
	// uint32_t size = m_childs.size();
	// for (uint32_t i = 0; i < size; ++i)
	// {
	// 	 auto child = childs[i];
	// 	 child->Destroy();
	// }
	// SafeDeleteArray(childs);
	// gameObject->Destroy();
}
