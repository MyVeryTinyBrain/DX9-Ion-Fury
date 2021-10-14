#pragma once

#ifdef _WIN64
#include "LibraryLink64.h"
#else
#include "LibraryLink86.h"
#endif

#include "EngineBase.h"
#include "Ref.h"
#include "Object.h"
#include "Component.h"
#include "Transform.h"
#include "GameObject.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Input.h"
#include "GlobalTime.h"
#include "GraphicDevice.h"
#include "Camera.h"
#include "Line.h"
#include "ResourceObject.h"
#include "Resource.h"
#include "Path.h"
#include "Texture.h"
#include "RenderTexture.h"
#include "Material.h"
#include "EngineWorld.h"

// Built In
#include "BuiltInResources.h"

// For Physics
#include "Collider.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "CapsuleCollider.h"
#include "RightTriangleCollider.h"
#include "TriangleCollider.h"
#include "Rigidbody.h"
#include "PhysicsDefines.h"
#include "PhysicsQueryTypes.h"
#include "PhysicsCallbackTypes.h"
#include "Physics.h"

// For SR
#include "UserMesh.h"
#include "UserMeshRenderer.h"
#include "UserMeshBillboardRenderer.h"
#include "CubeUserMesh.h"
#include "CyilinderUserMesh.h"
#include "SphereUserMesh.h"
#include "QuadUserMesh.h"
#include "CapsuleUserMesh.h"
#include "RightTriangleUserMesh.h"
#include "TriangleUserMesh.h"
#include "RightTriangleEmptySideUserMesh.h"
#include "RightTriangleBackSide.h"
#include "RightTriangleFrontSide.h"
#include "Light.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "DirectionalLight.h"

// For json
#include "../../json/json.h"