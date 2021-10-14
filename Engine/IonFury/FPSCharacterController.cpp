#include "stdafx.h"
#include "FPSCharacterController.h"
#include "FPSCamera.h"
#include "PhysicsLayers.h"
#include "FPSOrthoCamera.h"

void FPSCharacterController::Awake()
{
    // Physics::SetGravity(Vec3(0, -9.81f * 2.0f, 0));

    m_body = gameObject->AddComponent<Rigidbody>();
    m_body->SetRotationLockAxis(PhysicsAxis::All, true);
    m_body->interpolate = true;
    m_body->sleepThresholder = 5.0f;

    m_subObj = CreateGameObjectToChild(transform);

    m_colliderObj = CreateGameObjectToChild(m_subObj->transform);
    m_collider = m_colliderObj->AddComponent<CapsuleCollider>();
    m_collider->layerIndex = (uint8_t)PhysicsLayers::Player;
    m_collider->OnCollisionEnter += Function<void(const CollisionEnter&)>(this, &FPSCharacterController::OnCollisionEnter);
    m_collider->OnCollisionExit += Function<void(const CollisionExit&)>(this, &FPSCharacterController::OnCollisionExit);

    m_cameraObj = CreateGameObjectToChild(m_subObj->transform);
    m_camera = m_cameraObj->AddComponent<FPSCamera>();
    m_cameraObj->transform->localPosition = Vec3(0, 0.5f, 0);
    m_cameraObj->transform->eulerAngle = Vec3(0, 0, 0);
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

    float beforeHalfHeight = m_collider->halfHeight;
    if (Input::GetKey(Key::LCtrl))
    {
        m_collider->halfHeight = 0.001f;
    }
    else
    {
        m_collider->halfHeight = 0.5f;
    }
    if (beforeHalfHeight != m_collider->halfHeight)
    {
        m_body->SetRigidbodySleep(false);
    }

    if (!m_hasGround)
    {
        m_collider->friction = 0.0f;
    }
    else
    {
        m_collider->friction = 1.0f;
    }

    m_moveDirection.Normalize();

    if (m_moveDirection.sqrMagnitude() > 0)
    {
        PhysicsRay ray;
        ray.point = m_collider->transform->position;
        ray.direction = Vec3::down();
        ray.distance = m_collider->halfHeight + m_collider->radius * sqrtf(2.5f);
        RaycastHit hit;
        Physics::Raycast(hit, ray, 0xFFFFFFFF, PhysicsQueryType::All, m_body);

        float speedFactor = 1.0f;
        if (Input::GetKey(Key::LCtrl) && m_hasGround)
        {
            speedFactor = 0.35f;
        }
        else if (Input::GetKey(Key::LShift))
        {
            speedFactor = 1.65f;
        }

        Vec3 velocity;
        if (m_hasGround)
        {
            Quat q2 = Quat::FromToRotation(Vec3::up(), hit.normal);
            Quat q1 = Quat::FromEuler(0, m_camera->transform->eulerAngle.y, 0);
            velocity = q2 * q1 * m_moveDirection * m_speed * speedFactor;
        }
        else
        {
            velocity = Quat::FromEuler(0, m_camera->transform->eulerAngle.y, 0) * m_moveDirection * m_speed * speedFactor;
            velocity.y = m_body->velocity.y;
        }

        m_body->velocity = velocity;
    }

    m_moveDirection = Vec3::zero();
}

void FPSCharacterController::Update()
{
    if (Input::GetKey(Key::A))
        m_moveDirection.x = -1;
    if (Input::GetKey(Key::D))
        m_moveDirection.x = +1;
    if (Input::GetKey(Key::W))
        m_moveDirection.z = +1;
    if (Input::GetKey(Key::S))
        m_moveDirection.z = -1;

    if (m_moveDirection.sqrMagnitude() > 0)
        m_camera->fpsOrthoCamera->SetWalkingState(true);

    if (Input::GetKey(Key::LCtrl))
    {
        m_camera->fpsOrthoCamera->SetElaptionAccumulateScale(0.35f);
    }
    else if (Input::GetKey(Key::LShift))
    {
        m_camera->fpsOrthoCamera->SetElaptionAccumulateScale(1.65f);
        m_camera->camera->fov = Lerp(m_camera->camera->fov, 80, Time::DeltaTime() * 10.0f);
    }
    else
    {
        m_camera->camera->fov = Lerp(m_camera->camera->fov, 90, Time::DeltaTime() * 10.0f);
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
