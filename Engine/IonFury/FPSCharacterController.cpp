#include "stdafx.h"
#include "FPSCharacterController.h"
#include "FPSCamera.h"
#include "PhysicsLayers.h"

void FPSCharacterController::Awake()
{
    m_body = gameObject->AddComponent<Rigidbody>();
    m_body->SetRotationLockAxis(PhysicsAxis::All, true);
    m_body->linearDamping = 1.0f;
    m_body->interpolate = true;

    m_subObj = CreateGameObjectToChild(transform);

    m_colliderObj = CreateGameObjectToChild(m_subObj->transform);
    m_collider = m_colliderObj->AddComponent<CapsuleCollider>();
    m_collider->layerIndex = (uint8_t)PhysicsLayers::Player;
    m_collider->OnCollisionEnter += Function<void(const CollisionEnter&)>(this, &FPSCharacterController::OnCollisionEnter);
    m_collider->OnCollisionExit += Function<void(const CollisionExit&)>(this, &FPSCharacterController::OnCollisionExit);

    m_cameraObj = CreateGameObjectToChild(m_subObj->transform);
    m_camera = m_cameraObj->AddComponent<FPSCamera>();
    m_cameraObj->transform->localPosition = Vec3(0, 0.5f, 0);
    m_cameraObj->transform->eulerAngle = Vec3(0, 90, 0);
}

void FPSCharacterController::FixedUpdate()
{
    PhysicsRay ray;
    ray.point = m_collider->transform->position;
    ray.direction = Vec3::down();
    ray.distance = m_collider->halfHeight + m_collider->radius * sqrtf(2.5f);
    m_hasGround = Physics::RaycastTest(ray, 0xFFFFFFFF, PhysicsQueryType::All, m_body);
    
    if (Input::GetKey(Key::Space))
    {
        if (m_hasGround)
        {
            Vec3 velocity = m_body->velocity;
            velocity.y = m_jumpSpeed;
            m_body->velocity = velocity;

            transform->position += Vec3::up() * 0.05f;
            m_body->ApplyBodyTransformFromGameObject();
            m_hasGround = false;
        }
    }

    if (!m_hasGround)
    {
        m_collider->friction = 0.0f;
    }
    else
    {
        m_collider->friction = 1.0f;
    }

    Vec3 direction;
    if (Input::GetKey(Key::A))
        direction.x = -1;
    if (Input::GetKey(Key::D))
        direction.x = +1;
    if (Input::GetKey(Key::W))
        direction.z = +1;
    if (Input::GetKey(Key::S))
        direction.z = -1;
    direction.Normalize();

    if (direction.sqrMagnitude() > 0)
    {
        PhysicsRay ray;
        ray.point = m_collider->transform->position;
        ray.direction = Vec3::down();
        ray.distance = m_collider->halfHeight + m_collider->radius * sqrtf(2.5f);
        RaycastHit hit;
        Physics::Raycast(hit, ray, 0xFFFFFFFF, PhysicsQueryType::All, m_body);

        Vec3 velocity;
        if (m_hasGround)
        {
            Quat q2 = Quat::FromToRotation(Vec3::up(), hit.normal);
            Quat q1 = Quat::FromEuler(0, m_camera->transform->eulerAngle.y, 0);
            velocity = q2 * q1 * direction * m_speed;
        }
        else
        {
            velocity = m_camera->transform->rotation * direction * m_speed;
            velocity.y = m_body->velocity.y;
        }

        m_body->velocity = velocity;
    }

    if (Input::GetKey(Key::LCtrl))
    {
        m_collider->halfHeight = 0.01f;
    }
    else
    {
        m_collider->halfHeight = 0.5f;
    }
}

void FPSCharacterController::Update()
{
    if (Input::GetKeyDown(Key::LeftMouse))
    {
        //m_orthoCamera->rightHandAnimator->PlayShoot();

        {
            auto obj = CreateGameObject();
            obj->transform->position = m_camera->transform->position + m_camera->transform->forward * 2.0f;
            auto body = obj->AddComponent<Rigidbody>();
            body->interpolate = true;
            auto collider = obj->AddComponent<BoxCollider>();
            auto renderer = obj->AddComponent<UserMeshRenderer>();
            renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);

            body->velocity = m_camera->transform->forward * 15;
        }
    }
}

void FPSCharacterController::OnDestroy()
{
    m_collider->OnCollisionEnter -= Function<void(const CollisionEnter&)>(this, &FPSCharacterController::OnCollisionEnter);
    m_collider->OnCollisionExit -= Function<void(const CollisionExit&)>(this, &FPSCharacterController::OnCollisionExit);
}

void FPSCharacterController::OnCollisionEnter(const CollisionEnter& collision)
{
}

void FPSCharacterController::OnCollisionExit(const CollisionExit& collision)
{
}

Rigidbody* FPSCharacterController::GetRigidbody() const
{
    return m_body;
}

CapsuleCollider* FPSCharacterController::GetCollider() const
{
    return m_collider;
}

FPSCamera* FPSCharacterController::GetFPSCamera() const
{
    return m_camera;
}

Camera* FPSCharacterController::GetCamera() const
{
    return m_camera->camera;
}
