#pragma once

enum class COMBOBOX { Cube, Cyilinder, Quad, Sphere, Capsule, RightTriangle, Triangle, END };
enum class Type { EventObject, Trigger, Map, TypeEnd };
enum class EventType { ArmoredMutant, Cultist, Deacon, Drone, GreaterCultist, Liberator,
	Mechsect, Mutant, Skinjob, Warmech, Wendigo, Door, EventObjectEnd };	//���� ���Ͱ� �������� ����
enum class TriggerMethod { Touch, Button, Manual, End };

enum class HandleObjectType { ItemBowAmmo, ItemChaingunAmmo, ItemLauncherAmmo,
	ItemRevolverAmmo, ItemShotgunAmmo, ItemSMGAmmo, ItemHealthPack, End};