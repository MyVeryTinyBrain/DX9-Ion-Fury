#include "EngineBase.h"
#include "LayerManager.h"
#include "PhysicsDevice.h"
#include "PhysicsDefines.h"
#include "Collider.h"

LayerManager::LayerManager()
{
	Reset();
}

LayerManager::~LayerManager()
{
}

void LayerManager::Reset()
{
	for (auto& u32 : m_filter)
	{
		u32 = 0;
	}

	SetLayerCollisions(0, 0, true);
}

void LayerManager::SetLayerCollisions(unsigned int layerIndexA, unsigned int layerIndexB, bool collision)
{
	assert(layerIndexA < PhysicsLayerMax);
	assert(layerIndexB < PhysicsLayerMax);

	if (layerIndexA < PhysicsLayerMax && layerIndexB < PhysicsLayerMax)
	{
		if (collision)
		{
			m_filter[layerIndexA] |= (1 << layerIndexB);
			m_filter[layerIndexB] |= (1 << layerIndexA);
		}
		else
		{
			m_filter[layerIndexA] &= !(1 << layerIndexB);
			m_filter[layerIndexB] &= !(1 << layerIndexA);
		}
		UpdateActorFilters();
	}
}

bool LayerManager::IsCollisionLayers(unsigned int layerIndexA, unsigned int layerIndexB)
{
	assert(layerIndexA < PhysicsLayerMax);
	assert(layerIndexB < PhysicsLayerMax);

	if (layerIndexA < PhysicsLayerMax && layerIndexB < PhysicsLayerMax)
	{
		return m_filter[layerIndexA] & (1 << layerIndexB);
	}

	return false;
}

PxU32 LayerManager::GetCollisionBits(unsigned int layerIndex) const
{
	assert(layerIndex < PhysicsLayerMax);

	if (layerIndex < PhysicsLayerMax)
	{
		return m_filter[layerIndex];
	}

	return 0x00000000;
}

void LayerManager::UpdateActorFilters()
{
	PxActorTypeFlags actorTypes = PxActorTypeFlag::eRIGID_STATIC | PxActorTypeFlag::eRIGID_DYNAMIC;

	auto scene = PhysicsDevice::GetInstance()->GetScene();

	PxU32 nbActors = scene->getNbActors(actorTypes);
	PxActor** actors = new PxActor * [nbActors];

	scene->getActors(actorTypes, actors, sizeof(PxActor*) * nbActors);

	for (PxU32 i = 0; i < nbActors; ++i)
	{
		PxActorType::Enum type = actors[i]->getType();
		
		bool isRigidBody = type & (PxActorType::Enum::eRIGID_STATIC | PxActorType::Enum::eRIGID_DYNAMIC);

		if (!isRigidBody)
			continue;

		PxRigidActor* actor = static_cast<PxRigidActor*>(actors[i]);

		PxU32 nbShapes = actor->getNbShapes();
		PxShape** shapes = new PxShape * [nbShapes];
		actor->getShapes(shapes, sizeof(PxU32) * nbShapes);

		for (PxU32 j = 0; j < nbShapes; ++j)
		{
			PxShape* shape = shapes[j];
			Collider* collider = (Collider*)shape->userData;
			collider->ApplyLayer();
		}

		SafeDeleteArray(shapes);
	}

	SafeDeleteArray(actors);
}
