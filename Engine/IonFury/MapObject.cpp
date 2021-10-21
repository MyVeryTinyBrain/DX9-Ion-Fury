#include "stdafx.h"
#include "MapObject.h"

void MapObject::OnDestroy()
{
	if (m_mesh)
	{
		m_mesh->ReleaseUnmanaged();
		m_mesh = nullptr;
	}
}

void MapObject::InitializeMapObject(const wstring& textureLocalPath, const Vec2& uvScale, int iMeshType, bool hasCollider)
{
	m_renderer = gameObject->AddComponent<UserMeshRenderer>();
	m_renderer->material = Resource::FindAs<Material>(BuiltInGeometryMaterial);

	m_renderer->SetTexture(0, Resource::FindAs<Texture>(textureLocalPath));

	enum { Cube, Cyilinder, Quad, Sphere, Capsule, RightTriangle, Triangle, END };
	if ((uvScale.sqrMagnitude() - 1.0f) <= FLT_EPSILON)
	{
		switch (iMeshType)
		{
			case Cube:
				m_renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
				break;
			case Cyilinder:
				m_renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCyilinderUserMesh);
				break;
			case Quad:
				m_renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadUserMesh);
				break;
			case Sphere:
				m_renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInSphereUserMesh);
				break;
			case Capsule:
				m_renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCapsuleUserMesh);
				break;
			case RightTriangle:
				m_renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInRightTriangleUserMesh);
				break;
			case Triangle:
				m_renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInTriangleUserMesh);
				break;
		}
	}
	else
	{
		switch (iMeshType)
		{
			case Cube:
				m_mesh = UserMesh::CreateUnmanaged<CubeUserMesh>();
				break;
			case Cyilinder:
				m_mesh = UserMesh::CreateUnmanaged<CyilinderUserMesh>();
				break;
			case Quad:
				m_mesh = UserMesh::CreateUnmanaged<QuadUserMesh>();
				break;
			case Sphere:
				m_mesh = UserMesh::CreateUnmanaged<SphereUserMesh>();
				break;
			case Capsule:
				m_mesh = UserMesh::CreateUnmanaged<CapsuleUserMesh>();
				break;
			case RightTriangle:
				m_mesh = UserMesh::CreateUnmanaged<RightTriangleUserMesh>();
				break;
			case Triangle:
				m_mesh = UserMesh::CreateUnmanaged<TriangleUserMesh>();
				break;
		}

		if (m_mesh)
		{
			m_mesh->uvScale = uvScale;
		}

		m_renderer->userMesh = m_mesh;
	}

	if (hasCollider)
	{
		switch (iMeshType)
		{
			case Cube:
				m_collider = gameObject->AddComponent<BoxCollider>();
				break;
			case Cyilinder:
				m_collider = gameObject->AddComponent<BoxCollider>();
				break;
			case Quad:
				{
					auto colliderObj = CreateGameObjectToChild(transform);
					colliderObj->transform->localPosition = Vec3(0, 0, -0.005f);
					colliderObj->transform->localScale = Vec3(1, 1, 0.01f);
					m_collider = colliderObj->AddComponent<BoxCollider>();
					//{
					//	auto debugRenderer = colliderObj->AddComponent<UserMeshRenderer>();
					//	debugRenderer->material = Resource::FindAs<Material>(BuiltInTransparentMaterial);
					//	debugRenderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInTransparentGreenTexture));
					//	debugRenderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
					//}
				}
				break;
			case Sphere:
				m_collider = gameObject->AddComponent<SphereCollider>();
				break;
			case Capsule:
				m_collider = gameObject->AddComponent<CapsuleCollider>();
				break;
			case RightTriangle:
				m_collider = gameObject->AddComponent<RightTriangleCollider>();
				break;
			case Triangle:
				m_collider = gameObject->AddComponent<TriangleCollider>();
				break;
		}


		if (m_collider)
		{
			m_collider->friction = 1.0f;
			m_collider->restitution = 1.0f;

			m_body = gameObject->AddComponent<Rigidbody>();
			m_body->isKinematic = true;
		}
	}
}
