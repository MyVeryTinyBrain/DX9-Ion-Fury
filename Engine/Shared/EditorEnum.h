#pragma once

enum class COMBOBOX { Cube, Cyilinder, Quad, Sphere, Capsule, RightTriangle, Triangle, END };
enum class Type { EventObject, Trigger, Map, TypeEnd };

enum class EventType { BasicMutant, Mutant, CultistArcher, CultistGunner, Deacon, Drone, Liberator,
	Spider, Skull, Warmech, Wendigo, Door, EventObjectEnd };	//���� ���Ͱ� �������� ����
enum class TriggerMethod { Touch, Button, Manual, CardCheck, End };

enum class HandleObjectType { ItemBowAmmo, ItemChaingunAmmo, ItemLauncherAmmo,
	ItemRevolverAmmo, ItemShotgunAmmo, ItemSMGAmmo, ItemHealthPack,
	ItemArmor, ItemCardKey, Mouse,
	End};