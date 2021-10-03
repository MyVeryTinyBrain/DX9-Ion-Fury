#include "EngineBase.h"
#include "PhysicsDevice.h"
#include "PhysicsDefines.h"
#include "LayerManager.h"
#include "PhysicsFilterShader.h"

ImplementSingletone(PhysicsDevice);

PhysicsDevice::PhysicsDevice()
{
}

PhysicsDevice::~PhysicsDevice()
{
	Release();
}

void PhysicsDevice::Initialize()
{
	m_filterShader = new PhysicsFilterShader;

	m_allocater = new PxDefaultAllocator;

	m_errorCallback = new PxDefaultErrorCallback;

	m_foundation = PxCreateFoundation(PX_PHYSICS_VERSION, *m_allocater, *m_errorCallback);

	m_physics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_foundation, PxTolerancesScale(), true);

	m_dispatcher = PxDefaultCpuDispatcherCreate(2);

	m_cooking = PxCreateCooking(PX_PHYSICS_VERSION, *m_foundation, PxCookingParams(m_physics->getTolerancesScale()));

	CreateScene();

	m_layerManager = new LayerManager;
}

void PhysicsDevice::Release()
{
	SafeDeleteInline(m_layerManager);

	PxRelease(m_scene);

	PxRelease(m_cooking);

	PxRelease(m_dispatcher);

	PxRelease(m_physics);

	PxRelease(m_foundation);

	SafeDelete(m_errorCallback);

	SafeDelete(m_allocater);

	SafeDelete(m_filterShader);
}

void PhysicsDevice::Step(float deltaTime)
{
	if (!m_scene)
		return;

	if (deltaTime <= 0)
		return;

	m_scene->simulate(deltaTime);
	m_scene->fetchResults(true);
}

PxPhysics* PhysicsDevice::GetPhysics() const
{
	return m_physics;
}

PxCooking* PhysicsDevice::GetCooking() const
{
	return m_cooking;
}

PxScene* PhysicsDevice::GetScene() const
{
	return m_scene;
}

LayerManager* PhysicsDevice::GetLayerManager() const
{
	return m_layerManager;
}

void PhysicsDevice::CreateScene()
{
	PxSceneDesc desc(m_physics->getTolerancesScale());

	desc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
	desc.cpuDispatcher = m_dispatcher;
	desc.filterShader = PhysicsFilterShader::PxSimulationFilterShader;
	desc.filterCallback = m_filterShader;

	auto scene = m_physics->createScene(desc);

	if (!scene)
		return;

	//desc.flags |=
	//	PxSceneFlag::eMUTABLE_FLAGS |
	//	PxSceneFlag::eENABLE_CCD |
	//	PxSceneFlag::eADAPTIVE_FORCE |
	//	PxSceneFlag::eENABLE_PCM |
	//	PxSceneFlag::eENABLE_FRICTION_EVERY_ITERATION;

	//// 연속 충돌 감지(Continuous Contact Detection) 활성화
	//// 아래 플래그를 사용할수 있습니다.
	//// PxPairFlag::eDETECT_CCD_CONTACT
	//// PxRigidBodyFlag::eENABLE_CCD
	//// 기본값: 비활성화
	//scene->setFlag(PxSceneFlag::eENABLE_CCD, true);

	//// Solver의 근사값 수렴을 가속합니다.
	//// 우선은 Warm Starting 으로 이해합니다.
	//// 기본값: 비활성화
	//scene->setFlag(PxSceneFlag::eADAPTIVE_FORCE, true);

	//// 영구 접점 매니폴드(Permanent Contact Manifold) 를 사용하는 GJK 기반 충돌 감지를 활성화합니다.
	//// 비활성화하면 SAT 기반 충돌 감지를 사용합니다.
	//// SAT는 안정적인 스태킹을 보장합니다.
	//// GJK는 SAT에 비해 안정성이 저하되는 스태킹이 생길수 있습니다.
	//// 하지만 성능과 메모리 측면에서 SAT에 비해 매우 효율적입니다.
	//// 기본값: 활성화
	//scene->setFlag(PxSceneFlag::eENABLE_PCM, true);

	//// 스레드에서 PxScene에 읽기/쓰기를 위해 PxScene을 잠글수 있습니다.
	//// PxScene의 멤버 함수를 이용해 씬을 잠글수 있습니다.
	//// PxScene::lockRead
	//// PxScene::unlockRead
	//// PxScene::lockWrite
	//// PxScene::unlockWrite
	//// 코드블록 잠금 클래스를 이용해 씬을 잠글수 있습니다.
	//// PxSceneWriteLock
	//// PxSceneReadLock
	//// 기본값: 비활성화
	//scene->setFlag(PxSceneFlag::eREQUIRE_RW_LOCK, false);

	//// Solver에서 추가 안정화 처리를 진행합니다.
	//// 이것은 많은 강체간의 상호작용 안정성을 향상시킵니다.
	//// 또한 약간의 운동량 손실을 초래할수 있으며 [실험적]인 기능입니다.
	//scene->setFlag(PxSceneFlag::eENABLE_STABILIZATION, false);

	//// 접점 매니폴드에서 추가 접점을 생성하여 평균 지점을 나타냅니다.
	//// 이것은 적은 수의 Solver Iteration이 사용되는 경우에 스태킹을 안정적으로 해줄수 있습니다.
	//scene->setFlag(PxSceneFlag::eENABLE_AVERAGE_POINT, false);

	//// 모든 Solver Iteration에서 마찰을 처리합니다.
	//// 이것은 성능과 안정성간의 적절한 균형을 제공합니다.
	//// 게임 개발에 어울리는 플래그입니다.
	//scene->setFlag(PxSceneFlag::eENABLE_FRICTION_EVERY_ITERATION, true);

	m_scene = scene;
}
