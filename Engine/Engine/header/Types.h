#pragma once

typedef unsigned long index_t;

typedef unsigned long order_t;

typedef wstring tag_t;

typedef std::size_t size_t;

using GameObjectList = std::list<class GameObject*>;

// tag_t: Wide string tag
// GameObjectList: Game Objects
using GameObjectMap = std::unordered_map<tag_t, GameObjectList>;

using ComponentVector = std::vector<class Component*>;

enum class Axis 
{ 
	NONE = 0, 
	X = 1 << 0, 
	Y = 1 << 1, 
	Z = 1 << 2 
};

#include "Vertex.h"

#include "Index.h"

#include "MaterialTypes.h"
