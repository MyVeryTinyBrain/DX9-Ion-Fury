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

	// �浹 �ݹ����� �浹 �������� �����մϴ�.
	class PhysicsSimulationEventCallback* m_simulationEventCallback = nullptr;

	// Ʈ���� �浹 �������� �����մϴ�.
	class PhysicsTriggerEvent* m_triggerEvent = nullptr;
};

