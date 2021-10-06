#include "stdafx.h"
#include "FPSCharacterController.h"
#include "FPSCamera.h"

void FPSCharacterController::Awake()
{
    m_body = gameObject->AddComponent<Rigidbody>();
    m_body->SetRotationLockAxis(PhysicsAxis::All, true);
    m_body->linearDamping = 1.0f;

    m_subObj = CreateGameObjectToChild(transform);

    m_colliderObj = CreateGameObjectToChild(m_subObj->transform);
    m_collider = m_colliderObj->AddComponent<CapsuleCollider>();

    m_cameraObj = CreateGameObjectToChild(m_subObj->transform);
    m_camera = m_cameraObj->AddComponent<FPSCamera>();

    Physics::SetGravity(Vec3(0.0f, -9.81f, 0.0f));
}

void FPSCharacterController::FixedUpdate()
{
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
}

void FPSCharacterController::Update()
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
