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
