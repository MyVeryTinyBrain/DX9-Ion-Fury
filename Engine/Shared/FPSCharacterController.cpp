#include "shared_stdafx.h"
#include "FPSCharacterController.h"
#include "FPSCamera.h"
#include "PhysicsLayers.h"
#include "FPSOrthoCamera.h"
#include "SoundMgr.h"

void FPSCharacterController::Awake()
{
    // Physics::SetGravity(Vec3(0, -9.81f * 2.0f, 0));

    m_body = gameObject->AddComponent<Rigidbody>();
    m_body->SetRotationLockAxis(PhysicsAxis::All, true);
    m_body->interpolate = Interpolate::Interpolate;
    m_body->sleepThresholder = 5.0f;

    m_subObj = CreateGameObjectToChild(transform);

    m_colliderObj = CreateGameObjectToChild(m_subObj->transform);
    m_collider = m_colliderObj->AddComponent<CapsuleCollider>();
    m_collider->layerIndex = (uint8_t)PhysicsLayers::Player;
    m_collider->OnCollisionEnter += Function<void(const CollisionEnter&)>(this, &FPSCharacterController::OnCollisionEnter);
    m_collider->OnCollisionExit += Function<void(const CollisionExit&)>(this, &FPSCharacterController::OnCollisionExit);
    m_collider->OnCollisionStay += Function<void(const CollisionStay&)>(this, &FPSCharacterController::OnCollisionStay);

    m_cameraObj = CreateGameObjectToChild(m_subObj->transform);
    m_camera = m_cameraObj->AddComponent<FPSCamera>();
    m_cameraObj->transform->localPosition = Vec3(0, 0.5f, 0);
    m_cameraObj->transform->eulerAngle = Vec3(0, 0, 0);
}

void FPSCharacterController::FixedUpdate()
{
    if (m_hasGround)
    {
		PhysicsRay ray;
		ray.point = m_collider->transform->position;
		ray.direction = Vec3::down();
        ray.distance = m_collider->halfHeight + m_collider->radius * 2.0f;
		m_hasGround = Physics::RaycastTest(ray, 1 << (uint8_t)PhysicsLayers::Terrain, PhysicsQueryType::All, m_body);
    }

    if (Input::GetKey(Key::Space))
    {
        PhysicsRay ray(m_collider->transform->position, Vec3::up(), 1.2f);
        bool hit = Physics::RaycastTest(ray, 1 << (uint8_t)PhysicsLayers::Terrain, PhysicsQueryType::Collider);

        if (m_hasGround && !hit)
        {
            Vec3 velocity = m_body->velocity;
            velocity.y = m_jumpSpeed;
            m_body->velocity = velocity;

            transform->position += Vec3::up() * 0.05f;
            m_body->ApplyBodyTransformFromGameObject();
            m_hasGround = false;

            int soundIndex = rand() % 5;
            wchar_t buffer[256];
            swprintf_s(buffer, L"../SharedResource/Sound/footstep/jump%d.ogg", soundIndex);
            SoundMgr::Play(buffer, CHANNELID::PLAYER_FOOTSTEP_JUMP);
        }
    }

    float beforeHalfHeight = m_collider->halfHeight;
    if (Input::GetKey(Key::LCtrl))
    {
        m_collider->halfHeight = m_crouchHalfHeight;
    }
    else if(m_collider->halfHeight != 0.5f)
    {
        PhysicsRay ray(m_collider->transform->position, Vec3::up(), 1.2f);
        bool hit = Physics::RaycastTest(ray, 1 << (uint8_t)PhysicsLayers::Terrain, PhysicsQueryType::Collider);
        if (!hit)
        {
            m_collider->halfHeight = m_standHalfHeight;
        }
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
        ray.distance = FLT_MAX;
        RaycastHit hit;
        Physics::Raycast(hit, ray, 1 << (uint8_t)PhysicsLayers::Terrain, PhysicsQueryType::Collider);

        float speedFactor = 1.0f;
        if (m_hasGround && m_collider->halfHeight != m_standHalfHeight)
        {
            speedFactor = 0.35f;
        }
        else if (m_hasGround && Input::GetKey(Key::LShift))
        {
            speedFactor = 1.65f;
        }

        m_footstepCounter -= Time::FixedDeltaTime() * speedFactor;

        if (m_footstepCounter <= 0 && m_hasGround)
        {
            int soundIndex = rand() % 3;
            wchar_t buffer[256];
            swprintf_s(buffer, L"../SharedResource/Sound/footstep/run%d.ogg", soundIndex);
            SoundMgr::Play(buffer, CHANNELID::PLAYER_FOOTSTEP);

            m_footstepCounter = m_footstepDelay;
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

    m_hasGround = false;
}

void FPSCharacterController::Update()
{
    if (Input::GetKeyDown(Key::NumAdd))
    {
        Time::SetTimeScale(3.0f);
        Time::SetFixedTimeScale(3.0f);
    }
    if (Input::GetKeyDown(Key::NumSubtract))
    {
        Time::SetTimeScale(1.0f);
        Time::SetFixedTimeScale(1.0f);
    }

    if (Input::GetKey(Key::Space))
        m_body->SetRigidbodySleep(false);

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

    if (m_collider->halfHeight != m_standHalfHeight)
    {
        m_camera->fpsOrthoCamera->SetElaptionAccumulateScale(0.35f);
    }
    else if (Input::GetKeyUp(Key::LCtrl))
    {
        m_body->AddForce(Vec3::up() * 0.1f, ForceMode::Force);
    }
    else if (Input::GetKey(Key::LShift))
    {
        m_camera->fpsOrthoCamera->SetElaptionAccumulateScale(1.65f);
    }

    if (Input::GetKeyDown(Key::E))
    {
        m_camera->UseInput();
    }
}

void FPSCharacterController::OnDestroy()
{
    m_collider->OnCollisionEnter -= Function<void(const CollisionEnter&)>(this, &FPSCharacterController::OnCollisionEnter);
    m_collider->OnCollisionExit -= Function<void(const CollisionExit&)>(this, &FPSCharacterController::OnCollisionExit);
    m_collider->OnCollisionStay -= Function<void(const CollisionStay&)>(this, &FPSCharacterController::OnCollisionStay);
}

void FPSCharacterController::OnCollisionEnter(const CollisionEnter& collision)
{
    float angle = Vec3::Angle(Vec3::up(), collision.GetContact(0).normal);

    if (angle < 49.9f && fabsf(collision.GetContact(0).impulse.y) > 4.0f)
    {
        int soundIndex = rand() % 3;
        wchar_t buffer[256];
        swprintf_s(buffer, L"../SharedResource/Sound/footstep/land%d.ogg", soundIndex);
        SoundMgr::Play(buffer, CHANNELID::PLAYER_FOOTSTEP_LAND);
    }
}

void FPSCharacterController::OnCollisionExit(const CollisionExit& collision)
{
}

void FPSCharacterController::OnCollisionStay(const CollisionStay& collision)
{
    float angle = Vec3::Angle(Vec3::up(), collision.GetContact(0).normal);

    if (angle < 49.9f)
    {
        m_hasGround = true;
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
