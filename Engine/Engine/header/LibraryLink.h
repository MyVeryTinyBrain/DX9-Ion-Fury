#pragma once

// DirectX 9

#pragma comment(lib, "d3d9.lib")

#pragma comment(lib, "d3dx9.lib")

// PhysX 4.1

#ifdef WIN32
#pragma comment(lib, "LowLevel_static_32.lib")
#pragma comment(lib, "LowLevelAABB_static_32.lib")
#pragma comment(lib, "LowLevelDynamics_static_32.lib")
#pragma comment(lib, "PhysX_32.lib")
#pragma comment(lib, "PhysXCharacterKinematic_static_32.lib")
#pragma comment(lib, "PhysXCommon_32.lib")
#pragma comment(lib, "PhysXCooking_32.lib")
#pragma comment(lib, "PhysXExtensions_static_32.lib")
#pragma comment(lib, "PhysXFoundation_32.lib")
#pragma comment(lib, "PhysXPvdSDK_static_32.lib")
#pragma comment(lib, "PhysXTask_static_32.lib")
#pragma comment(lib, "PhysXVehicle_static_32.lib")
#pragma comment(lib, "SceneQuery_static_32.lib")
#pragma comment(lib, "SimulationController_static_32.lib")
#else
#pragma comment(lib, "LowLevel_static_64.lib")
#pragma comment(lib, "LowLevelAABB_static_64.lib")
#pragma comment(lib, "LowLevelDynamics_static_64.lib")
#pragma comment(lib, "PhysX_64.lib")
#pragma comment(lib, "PhysXCharacterKinematic_static_64.lib")
#pragma comment(lib, "PhysXCommon_64.lib")
#pragma comment(lib, "PhysXCooking_64.lib")
#pragma comment(lib, "PhysXExtensions_static_64.lib")
#pragma comment(lib, "PhysXFoundation_64.lib")
#pragma comment(lib, "PhysXPvdSDK_static_64.lib")
#pragma comment(lib, "PhysXTask_static_64.lib")
#pragma comment(lib, "PhysXVehicle_static_64.lib")
#pragma comment(lib, "SceneQuery_static_64.lib")
#pragma comment(lib, "SimulationController_static_64.lib")
#endif