#pragma once

enum class COMBOBOX { Cube, Cyilinder, Quad, Sphere, Capsule, RightTriangle, Triangle, END };
enum class Type { EventObject, Trigger, Map, TypeEnd };
enum class EventType { Monster0, Monster1, Monster2, Monster3, Door1, Door2, Door3, EventObjectEnd };	//추후 몬스터가 정해지면 수정
enum class TriggerMethod { Touch, Button, Manual, End };

enum class HandleObjectType { ItemBowAmmo, ItemChaingunAmmo, ItemLauncherAmmo,
	ItemRevolverAmmo, ItemShotgunAmmo, ItemSMGAmmo, ItemHealthPack, End};