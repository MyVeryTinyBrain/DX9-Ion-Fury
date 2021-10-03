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

	//// ���� �浹 ����(Continuous Contact Detection) Ȱ��ȭ
	//// �Ʒ� �÷��׸� ����Ҽ� �ֽ��ϴ�.
	//// PxPairFlag::eDETECT_CCD_CONTACT
	//// PxRigidBodyFlag::eENABLE_CCD
	//// �⺻��: ��Ȱ��ȭ
	//scene->setFlag(PxSceneFlag::eENABLE_CCD, true);

	//// Solver�� �ٻ簪 ������ �����մϴ�.
	//// �켱�� Warm Starting ���� �����մϴ�.
	//// �⺻��: ��Ȱ��ȭ
	//scene->setFlag(PxSceneFlag::eADAPTIVE_FORCE, true);

	//// ���� ���� �Ŵ�����(Permanent Contact Manifold) �� ����ϴ� GJK ��� �浹 ������ Ȱ��ȭ�մϴ�.
	//// ��Ȱ��ȭ�ϸ� SAT ��� �浹 ������ ����մϴ�.
	//// SAT�� �������� ����ŷ�� �����մϴ�.
	//// GJK�� SAT�� ���� �������� ���ϵǴ� ����ŷ�� ����� �ֽ��ϴ�.
	//// ������ ���ɰ� �޸� ���鿡�� SAT�� ���� �ſ� ȿ�����Դϴ�.
	//// �⺻��: Ȱ��ȭ
	//scene->setFlag(PxSceneFlag::eENABLE_PCM, true);

	//// �����忡�� PxScene�� �б�/���⸦ ���� PxScene�� ��ۼ� �ֽ��ϴ�.
	//// PxScene�� ��� �Լ��� �̿��� ���� ��ۼ� �ֽ��ϴ�.
	//// PxScene::lockRead
	//// PxScene::unlockRead
	//// PxScene::lockWrite
	//// PxScene::unlockWrite
	//// �ڵ��� ��� Ŭ������ �̿��� ���� ��ۼ� �ֽ��ϴ�.
	//// PxSceneWriteLock
	//// PxSceneReadLock
	//// �⺻��: ��Ȱ��ȭ
	//scene->setFlag(PxSceneFlag::eREQUIRE_RW_LOCK, false);

	//// Solver���� �߰� ����ȭ ó���� �����մϴ�.
	//// �̰��� ���� ��ü���� ��ȣ�ۿ� �������� ����ŵ�ϴ�.
	//// ���� �ణ�� ��� �ս��� �ʷ��Ҽ� ������ [������]�� ����Դϴ�.
	//scene->setFlag(PxSceneFlag::eENABLE_STABILIZATION, false);

	//// ���� �Ŵ����忡�� �߰� ������ �����Ͽ� ��� ������ ��Ÿ���ϴ�.
	//// �̰��� ���� ���� Solver Iteration�� ���Ǵ� ��쿡 ����ŷ�� ���������� ���ټ� �ֽ��ϴ�.
	//scene->setFlag(PxSceneFlag::eENABLE_AVERAGE_POINT, false);

	//// ��� Solver Iteration���� ������ ó���մϴ�.
	//// �̰��� ���ɰ� ���������� ������ ������ �����մϴ�.
	//// ���� ���߿� ��︮�� �÷����Դϴ�.
	//scene->setFlag(PxSceneFlag::eENABLE_FRICTION_EVERY_ITERATION, true);

	m_scene = scene;
}
