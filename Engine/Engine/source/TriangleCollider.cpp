#include "EngineBase.h"
#include "TriangleCollider.h"
#include "PhysicsDevice.h"
#include "TriangleUserMesh.h"
#include "PhysicsDefines.h"
#include "Transform.h"
#include "BuiltInResources.h"
#include "Resource.h"

void TriangleCollider::Awake()
{
    TriangleUserMesh* mesh = Resource::FindAs<TriangleUserMesh>(BuiltInTriangleUserMesh);

    auto device = PhysicsDevice::GetInstance();

    Vec3* vertices = new Vec3[mesh->GetNumVertices()];
    for (unsigned int i = 0; i < mesh->GetNumVertices(); ++i)
        vertices[i] = mesh->GetStoredVertexBuffer()[i].position;

    PxConvexMeshDesc  desc;
    desc.points.count = mesh->GetNumVertices();
    desc.points.stride = sizeof(Vec3);
    desc.points.data = vertices;

    desc.indices.count = mesh->GetNumFaces();
    desc.indices.stride = sizeof(Index);
    desc.indices.data = mesh->GetStoredIndexBuffer();

    desc.flags = PxConvexFlag::eCOMPUTE_CONVEX;

    PxDefaultMemoryOutputStream writeBuffer;
    PxConvexMeshCookingResult::Enum result;
    bool cookingTriangleStatus = device->cooking->cookConvexMesh(desc, writeBuffer, &result);
    assert(cookingTriangleStatus);

    PxDefaultMemoryInputData readBuffer(writeBuffer.getData(), writeBuffer.getSize());

    m_mesh = device->physics->createConvexMesh(readBuffer);

    SafeDeleteArray(vertices);

    Collider::Awake();
}

PxGeometryHolder TriangleCollider::CreateGeometry()
{
    return CreateTriangleGeometry();
}

PxConvexMeshGeometry TriangleCollider::CreateTriangleGeometry() const
{
    PxMeshScale scale;
    scale.rotation = PxQuat(PxIdentity);
    scale.scale = ToPxVec3(transform->scale);
    return PxConvexMeshGeometry(m_mesh, scale);
}