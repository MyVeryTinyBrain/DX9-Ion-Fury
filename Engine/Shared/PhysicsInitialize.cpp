#include "shared_stdafx.h"
#include "PhysicsInitialize.h"
#include "PhysicsLayers.h"

void PhysicsInitialize::Initialize()
{
	Physics::SetLayerCollisions((unsigned int)PhysicsLayers::Terrain, (unsigned int)PhysicsLayers::Terrain, true);
	Physics::SetLayerCollisions((unsigned int)PhysicsLayers::Terrain, (unsigned int)PhysicsLayers::Player, true);
	Physics::SetLayerCollisions((unsigned int)PhysicsLayers::Terrain, (unsigned int)PhysicsLayers::Monster, true);
	Physics::SetLayerCollisions((unsigned int)PhysicsLayers::Terrain, (unsigned int)PhysicsLayers::MonsterDeadBody, true);
	Physics::SetLayerCollisions((unsigned int)PhysicsLayers::Terrain, (unsigned int)PhysicsLayers::Projectile, true);
	Physics::SetLayerCollisions((unsigned int)PhysicsLayers::Player, (unsigned int)PhysicsLayers::Monster, true);
	Physics::SetLayerCollisions((unsigned int)PhysicsLayers::Player, (unsigned int)PhysicsLayers::Projectile, true);
	Physics::SetLayerCollisions((unsigned int)PhysicsLayers::Monster, (unsigned int)PhysicsLayers::Monster, true);
	Physics::SetLayerCollisions((unsigned int)PhysicsLayers::Monster, (unsigned int)PhysicsLayers::Projectile, true);
}
