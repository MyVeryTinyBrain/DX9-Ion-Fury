#pragma once

class PhysicsDevice
{
	DeclareSingletone(PhysicsDevice);

private:

	PhysicsDevice();

	~PhysicsDevice();

public:

	void Initialize();

	void Release();

	void Step(float deltaTime);

	void Notify();

public:

	PxPhysics* GetPhysics() const;

	PxCooking* GetCooking() const;

	PxScene* GetScene() const;

	class LayerManager* GetLayerManager() const;

	__declspec(property(get = GetPhysics)) PxPhysics* physics;

	__declspec(property(get = GetCooking)) PxCooking* cooking;

	__declspec(property(get = GetScene)) PxScene* scene;

	__declspec(property(get = GetLayerManager)) class LayerManager* layerManager;

private:

	void CreateScene();

private:

	PxDefaultAllocator* m_allocater = nullptr;

	PxDefaultErrorCallback* m_errorCallback = nullptr;

	PxFoundation* m_foundation = nullptr;

	PxPhysics* m_physics = nullptr;

	PxDefaultCpuDispatcher* m_dispatcher = nullptr;

	PxCooking* m_cooking = nullptr;

	PxScene* m_scene = nullptr;

	class LayerManager* m_layerManager = nullptr;

	class PhysicsFilterShaderCallback* m_filterShaderCallback = nullptr;

	// 충돌 콜백으로 충돌 정보들을 생성합니다.
	class PhysicsSimulationEventCallback* m_simulationEventCallback = nullptr;

	// 트리거 충돌 정보들을 저장합니다.
	class PhysicsTriggerEvent* m_triggerEvent = nullptr;
};

