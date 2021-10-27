#include "stdafx.h"
#include "MainSceneComponent.h"
#include <RenderLayers.h>
#include <OverlayRenderOrders.h>
#include <SoundMgr.h>

#include "Map0.h"
#include "Map1.h"

bool MainSceneComponent::g_loaded = false;

void MainSceneComponent::Awake()
{
	{
		auto obj = CreateGameObject();
		obj->transform->position = Vec3(0, 0, -10);

		auto cam = obj->AddComponent<Camera>();
		cam->cameraOrder = 100;
		cam->overlapMode = true;
		cam->allowRenderLayers = (1 << uint8_t(RenderLayers::Overlay));
		cam->projectionMode = ProjectionMode::Orthographic;
	}

	{
		Texture::CreateFromFile(L"../SharedResource/Texture/main_scene/logo.png", false);
		Texture::CreateFromFile(L"../SharedResource/Texture/main_scene/pressanykey.png", false);
	}

	{
		MaterialParameters params;
		params.zRead = false;
		params.zWrite = false;
		params.alphaTest = true;
		params.alphaBlend = true;
		params.useLight = false;
		params.renderQueue = RenderQueue::Overlay;
		Material::Create(params, L"MainSceneOverlayMaterial", false);
	}

	{
		UserMesh::Create<QuadUserMesh>(L"MainSceneQuad", false);
	}

	Texture* logoTexture = Resource::FindAs<Texture>(L"../SharedResource/Texture/main_scene/logo.png");
	Texture* pressAnyKeyTexture = Resource::FindAs<Texture>(L"../SharedResource/Texture/main_scene/pressanykey.png");
	Material* overlayMaterial = Resource::FindAs<Material>(L"MainSceneOverlayMaterial");
	UserMesh* quad = Resource::FindAs<UserMesh>(L"MainSceneQuad");

	auto root = CreateGameObject();
	root->transform->position = Vec3(0, 0, 0);
	root->transform->scale = Vec3(Camera::GetMainCamera()->orthographicWidth, 1, 1);

	{
		auto obj = CreateGameObjectToChild(root->transform);
		auto renderer = obj->AddComponent<UserMeshRenderer>();
		renderer->material = overlayMaterial;
		renderer->userMesh = quad;
		renderer->renderLayerIndex = uint8_t(RenderLayers::Overlay);
		renderer->overlayRenderOrder = (int)OverlayRenderOrders::Logo;
		renderer->SetTexture(0, logoTexture);
	}

	{
		auto obj = CreateGameObjectToChild(root->transform);
		auto renderer = obj->AddComponent<UserMeshRenderer>();
		renderer->material = overlayMaterial;
		renderer->userMesh = quad;
		renderer->renderLayerIndex = uint8_t(RenderLayers::Overlay);
		renderer->overlayRenderOrder = (int)OverlayRenderOrders::PressAnyKey;
		renderer->SetTexture(0, pressAnyKeyTexture);

		m_pressAnyKeyRenderer = renderer;
		m_pressAnyKeyRenderer->enable = false;
	}

	{
		for (int i = 0; i < FADE_STEP; ++i)
		{
			float percent = float(i) / float(FADE_STEP - 1);
			m_fadeTexture[i] = Texture::CreateUnmanagedInDirectX(1, 1, Color(0, 0, 0, percent));
		}

		m_fadeImageObj = CreateGameObjectToChild(root->transform);

		m_fadeImageRenderer = m_fadeImageObj->AddComponent<UserMeshRenderer>();
		m_fadeImageRenderer->material = overlayMaterial;
		m_fadeImageRenderer->userMesh = quad;
		m_fadeImageRenderer->renderLayerIndex = uint8_t(RenderLayers::Overlay);
		m_fadeImageRenderer->overlayRenderOrder = (int)OverlayRenderOrders::LogoFade;
		m_fadeImageRenderer->SetTexture(0, m_fadeTexture[FADE_END]);
	}
}

void MainSceneComponent::Start()
{
	FadeOut();

	AsyncResourceLoad();
}

void MainSceneComponent::Update()
{
	if (m_readyToChangeScene && m_fadeAlpha >= 1.0f)
	{
		SceneManager::ChangeScene(new Map0);
	}

	if (g_loaded && !m_readyToChangeScene)
	{
		m_pressAnyKeyRenderer->enable = true;

		if (Input::GetKeyDown(Key::Return))
		{
			m_readyToChangeScene = true;
			FadeIn();
		}
	}
}

void MainSceneComponent::LateUpdate()
{
	// Fade effect =====================================================================

	// Fade Transition
	const float maxDT = 1.0f / 10.0f;
	float dt = Time::UnscaledDelteTime();
	if (dt > maxDT)
	{
		dt = maxDT;
	}

	if (m_fadeAlpha != m_targetFadeAlpha)
	{
		if (m_fadeAlpha < m_targetFadeAlpha)
		{
			m_fadeAlpha += dt * m_fadeSpeed;

			if (m_fadeAlpha >= m_targetFadeAlpha)
			{
				m_fadeAlpha = m_targetFadeAlpha;
			}
		}
		else
		{
			m_fadeAlpha -= dt * m_fadeSpeed;

			if (m_fadeAlpha <= m_targetFadeAlpha)
			{
				m_fadeAlpha = m_targetFadeAlpha;
			}
		}
	}

	// Fade texture change
	float fFadeIndex = m_fadeAlpha * float(FADE_END);
	int fadeIndex = int(fFadeIndex);

	m_fadeImageRenderer->SetTexture(0, m_fadeTexture[fadeIndex]);

	if (fadeIndex == 0)
	{
		m_fadeImageRenderer->enable = false;
	}
	else
	{
		m_fadeImageRenderer->enable = true;
	}

	// Fade effect =====================================================================
}

void MainSceneComponent::OnDestroy()
{
	for (int i = 0; i < FADE_STEP; ++i)
	{
		if (m_fadeTexture[i])
		{
			m_fadeTexture[i]->ReleaseUnmanaged();
			m_fadeTexture[i] = nullptr;
		}
	}

	if (m_resourceLoadThread.joinable())
		m_resourceLoadThread.join();
}

void MainSceneComponent::FadeIn(float time)
{
	m_targetFadeAlpha = 1.0f;

	if (time <= 0)
	{
		time = 0.0001f;
	}
	m_fadeSpeed = 1.0f / time;
}

void MainSceneComponent::FadeOut(float time)
{
	m_targetFadeAlpha = 0.0f;

	if (time <= 0)
	{
		time = 0.0001f;
	}
	m_fadeSpeed = 1.0f / time;
}

void MainSceneComponent::SetFadeAlpah(float value)
{
	value = Clamp(value, 0, 1);

	m_fadeAlpha = value;
}

float MainSceneComponent::GetFadeAlpha() const
{
	return m_fadeAlpha;
}

void MainSceneComponent::AsyncResourceLoad()
{
	if (!g_loaded)
	{
		std::thread t(
			[&]() 
			{ 
				BuiltIn::MakeBuiltInResources();
				SharedResourceLoader::LoadSharedResources();
				SoundMgr::Get_Instance()->LoadSoundFile();
				g_loaded = true;
			}
		);
		m_resourceLoadThread.swap(t);
	}
}
