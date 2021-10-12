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
	// 이 트랜스폼을 부모로 두려는 경우 종료합니다.
	if (parent == this) return;

	// 우선, 부모에서 탈퇴합니다.
	DetachFromParent();

	if (parent)
	{
		// 등록되려는 부모가 있다면
		// 새로운 부모의 자식으로 등록합니다.
		parent->AddChild(this);
	}
}

void Transform::DetachFromParent()
{
	if (!m_parent) return;

	// 부모가 있다면 부모에게서 탈퇴합니다.
	m_parent->RemoveChild(this);
}

void Transform::AddChild(Transform* child)
{
	// 이 트랜스폼을 자식으로 두려는 경우 종료합니다.
	if (child == this) return;

	if (!child) return;

	// ===============================================================
	// 특정한 경우에 부모로부터 탈퇴합니다.
	// 이 코드가 없으면 무한 순환이 생길 수 있습니다.
	// A-->B-->C (화살표는 자식을 나타냅니다.) 와 같은 관계가 있을 때
	// A 가 C 의 자식이 되는 경우에는 A-->B-->C-->A-->... 와 같이
	// 무한 순환이 생깁니다.
	// 이를 방지하기 위해서
	// 트리의 부모들에서 인자로 받은 child 트랜스폼이 부모로 존재한다면
	// 인자로 받은 child 트랜스폼은 인자로 받은 child 트랜스폼의 
	// 자식 중 하나인 이전 노드 it_prevParent를 자식에서 제거합니다.
	// 따라서 C-->A-->B 관계가 되고, 무한 순환이 깨집니다.
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

	// child 트랜스폼을을 부모로부터 탈퇴시킵니다. 
	child->DetachFromParent();

	// 추가되려는 child 트랜스폼의 부모를 이 트랜스폼으로 설정합니다.
	child->m_parent = this;

	// 이 트랜스폼의 자식에 추가되려는 child 트랜스폼을 추가합니다.
	m_childs.push_back(child);

	// 자식으로 추가된 child 트랜스폼을 업데이트합니다.

	child->UpdateLocalTransform(UpdateTransformArgument::None);

	child->UpdateActiveInTree();

}

void Transform::RemoveChild(Transform* child)
{
	if (!child) return;

	// child 트랜스폼이 자식으로 존재하지 않는다면 종료합니다.

	auto find_it = FindInContainer(m_childs, child);

	if (find_it == m_childs.end()) return;

	// child 트랜스폼을 자식 벡터에서 제거합니다.
	m_childs.erase(find_it);

	// child 트랜스폼의 부모를 없음으로 설정합니다.
	child->m_parent = nullptr;

	// 부모에서 탈퇴된 child 트랜스폼을 업데이트합니다.

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
	// 변경되기 전의 트리내 활성화 상태를 기록합니다.
	bool beforeActiveInTree = m_activeInTree;

	if (!m_parent)
	{
		// 부모가 없다면 트리의 최상단이므로 상위 트랜스폼에 영향을 받지 않습니다.
		// 이 때의 트리내 활성화 상태는 무조건 참입니다.
		m_activeInTree = true;
	}
	else
	{
		// 부모가 있는 경우에는
		// 부모가 활성화 되어있어야 하며, 부모의 트리내 활성화 상태도 참이어야 합니다.
		m_activeInTree = m_parent->m_activeInTree && m_parent->m_activeSelf;
	}

	if (m_activeInTree != beforeActiveInTree)
	{
		// 트리내 활성화 상태가 변경되었다면 isWake 플래그를 재설정하기 위해 이 함수를 호출합니다.
		OnEnableChanged();
	}

	for (auto child : m_childs)
	{
		// 자식들의 트리내 활성화 상태를 재설정합니다.
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
	// 이 트랜스폼이 파괴되는 경우에는
	// 부모에서 탈퇴되어야 하며
	// 자식들 역시 모두 떼어내야 합니다.
	// 이때 자식들을 순회하며 파괴 함수를 호출해 주어야 하는데
	// 자식 트랜스폼도 부모에서 탈퇴하는 작업을 진행하게 됩니다.
	// 이 작업이 겹치기 때문에 컨테이너를 순회하며 동시에 컨테이너에서 제거하는 것은 문제가 발생할 수 있습니다.
	// ===================================================================================================

	// Method 1
	// 부모에게서 탈퇴한 후
	// 벡터의 맨 뒤쪽 자식부터 하나씩 제거합니다.
	// 이때 Destroy 함수 호출시 부모 벡터에서 제거되므로
	// child->Destroy() 함수를 호출하는 것 만으로도 벡터에서 제거됩니다.

	DetachFromParent();
	gameObject->Destroy();
	while (!m_childs.empty())
	{
		auto child = m_childs.back();
		child->Destroy();
	}

	// Method 2
	// 자식을 복사해두고 순회하며 파괴하는 방법입니다.
	
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
