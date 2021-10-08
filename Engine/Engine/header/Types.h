#pragma once

typedef unsigned long index_t;

typedef unsigned long order_t;

typedef wstring tag_t;

typedef std::size_t size_t;

using GameObjectList = std::list<class GameObject*>;

using GameObjectMap = std::unordered_map<tag_t, GameObjectList>;

using ComponentVector = std::vector<class Component*>;

#include "Vertex.h"

#include "Index.h"

#include "MaterialTypes.h"
