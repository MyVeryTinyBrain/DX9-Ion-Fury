#include "shared_stdafx.h"
#include "MiniGame01.h"
#include "MiniGameCamera01.h"

void MiniGame01::Awake()
{
	m_CameraObj = CreateGameObject();
	m_CameraObj->AddComponent<MiniGameCamera01>();
}

void MiniGame01::Update()
{
}
