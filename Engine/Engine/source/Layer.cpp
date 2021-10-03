#include "EngineBase.h"
#include "Layer.h"
#include "PhysicsDevice.h"
#include "LayerManager.h"

void Layer::Reset()
{
    PhysicsDevice::GetInstance()->layerManager->Reset();
}

void Layer::SetLayerCollisions(unsigned int layerIndexA, unsigned int layerIndexB, bool collision)
{
    PhysicsDevice::GetInstance()->layerManager->SetLayerCollisions(layerIndexA, layerIndexB, collision);
}

bool Layer::IsCollisionLayers(unsigned int layerIndexA, unsigned int layerIndexB)
{
    return PhysicsDevice::GetInstance()->layerManager->IsCollisionLayers(layerIndexA, layerIndexB);
}

uint32_t Layer::GetCollisionBits(unsigned int layerIndex)
{
    return PhysicsDevice::GetInstance()->layerManager->GetCollisionBits(layerIndex);
}
