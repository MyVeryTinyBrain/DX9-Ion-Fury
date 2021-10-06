#include "EngineBase.h"
#include "RenderProcess.h"
#include "Renderer.h"
#include "Material.h"
#include "Camera.h"
#include "GraphicDevice.h"
#include "RenderTexture.h"
#include "Transform.h"
#include "Light.h"

void RenderProcess::ClearRenderTargets()
{
	for (auto& renderTargets : m_renderTargets)
	{
		renderTargets.clear();
	}
	m_transparentRenderTargets.clear();
}

void RenderProcess::AddRenderTarget(Renderer* renderer)
{
	const Ref<Material>& refMaterial = renderer->material;

	if (refMaterial.IsNull())
		return;

	Material* material = refMaterial.GetPointer();

	if (material->params.renderQueue == RenderQueue::Transparent)
	{
		// 투명 렌더 타겟이면 투명 렌더타겟 리스트에 추가합니다.

		TransparentRenderTarget transparentRenderTarget;
		transparentRenderTarget.renderer = renderer;
		transparentRenderTarget.distanceFromCamera = 0;
		m_transparentRenderTargets.push_back(std::move(transparentRenderTarget));
	}
	else
	{
		// 투명 렌더 타겟이 아니라면
		// 렌더타겟 맵의 Material로 분류되는 리스트에 추가합니다.

		auto& renderTargets = m_renderTargets[unsigned int(material->params.renderQueue)];
		renderTargets[material].push_back(renderer);
		int ff = 0;
	}
}

void RenderProcess::Process()
{
	auto device = GraphicDevice::GetInstance()->GetDevice();

	size_t cameraCount = Camera::GetCameraCount();

	for (unsigned int i = 0; i < cameraCount; ++i)
	{
		IDirect3DSurface9* mainRenderTarget = nullptr;
		device->GetRenderTarget(0, &mainRenderTarget);

		Camera* camera = Camera::GetCamera(i);

		if (!camera->isWake)
			continue;

		if (!camera->renderTexture.IsNull())
		{
			// 렌더 텍스쳐가 있는 경우에 
			// 메인 렌더 타겟을 저장해두고,
			// 렌더 타겟을 변경합니다.
			HRESULT res;
			RenderTexture* renderTexture = camera->renderTexture.GetPointer();
			IDirect3DSurface9* renderSurface = nullptr;
			res = renderTexture->GetTexture()->GetSurfaceLevel(0, &renderSurface);
			res = device->SetRenderTarget(0, renderSurface);

			device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, GraphicDevice::GetInstance()->GetBackgroundColor(), 1.0f, 0);
		}
		else if (camera->overlapMode)
		{
			// 덮어쓰기 모드이면 깊이 버퍼를 초기화해 화면에 덮어 그리도록 합니다.

			device->Clear(0, 0, D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, Color::white(), 1.0f, 0);
		}

		device->BeginScene();

		device->SetRenderState(D3DRS_NORMALIZENORMALS, true);

		Mat4 worldToView = camera->worldToView;
		device->SetTransform(D3DTS_VIEW, &worldToView);

		Mat4 viewToProjection = camera->viewToProjection;
		device->SetTransform(D3DTS_PROJECTION, &viewToProjection);

		Light::BeginLight();

		Render(camera);

		Light::EndLight();

		device->EndScene();

		if (!camera->renderTexture.IsNull())
		{
			// 렌더 텍스쳐가 있던 경우에는 다시 메인 렌더 타겟으로 되돌립니다.

			device->SetRenderTarget(0, mainRenderTarget);
		}
	}

	ClearRenderTargets();
}

void RenderProcess::Render(Camera* baseCamera)
{
	RenderTo(baseCamera, RenderQueue::Background);
	RenderTo(baseCamera, RenderQueue::Priority);
	RenderTo(baseCamera, RenderQueue::Geometry);
	RenderTo(baseCamera, RenderQueue::AlphaTest);
	RenderTo(baseCamera, RenderQueue::GeometryLast);

	RenderTransparent(baseCamera);

	RenderTo(baseCamera, RenderQueue::Overlay);
}

void RenderProcess::RenderTo(Camera* baseCamera, RenderQueue renderQueue)
{
	auto& renderTargetMap = m_renderTargets[unsigned int(renderQueue)];

	for (auto& mapElement : renderTargetMap)
	{
		auto& material = mapElement.first;
		auto& renderTargetList = mapElement.second;

		material->Apply();

		for (auto& renderer : renderTargetList)
		{
			bool draw = baseCamera->allowRenderLayers & (1 << renderer->renderLayerIndex);

			if (!draw)
				continue;

			renderer->Render();
		}
	}
}

void RenderProcess::RenderTransparent(Camera* baseCamera)
{
	// 카메라와의 거리를 계산합니다.
	const Vec3& cameraPosition = baseCamera->transform->position;
	for (auto& transparentRenderTarget : m_transparentRenderTargets)
	{
		auto& renderer = transparentRenderTarget.renderer;
		const Vec3& rendererPosition = renderer->transform->position;
		transparentRenderTarget.distanceFromCamera = Vec3::Distance(cameraPosition, rendererPosition);
	}

	// 카메라와의 거리가 먼 것이 리스트의 앞에 오도록 설정합니다.
	std::sort(
		m_transparentRenderTargets.begin(),
		m_transparentRenderTargets.end(),
		[](const TransparentRenderTarget& lhs, const TransparentRenderTarget& rhs)
		{
			return lhs.distanceFromCamera > rhs.distanceFromCamera;
		});

	// 정렬된 반투명 렌더타겟을 순서대로 그립니다.
	for (auto& transparentRenderTarget : m_transparentRenderTargets)
	{
		auto& renderer = transparentRenderTarget.renderer;
		auto& material = transparentRenderTarget.renderer->material;

		bool draw = baseCamera->allowRenderLayers & (1 << renderer->renderLayerIndex);

		if (!draw)
			continue;

		material->Apply();
		renderer->Render();
	}
}
