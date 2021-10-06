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
		// ���� ���� Ÿ���̸� ���� ����Ÿ�� ����Ʈ�� �߰��մϴ�.

		TransparentRenderTarget transparentRenderTarget;
		transparentRenderTarget.renderer = renderer;
		transparentRenderTarget.distanceFromCamera = 0;
		m_transparentRenderTargets.push_back(std::move(transparentRenderTarget));
	}
	else
	{
		// ���� ���� Ÿ���� �ƴ϶��
		// ����Ÿ�� ���� Material�� �з��Ǵ� ����Ʈ�� �߰��մϴ�.

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
			// ���� �ؽ��İ� �ִ� ��쿡 
			// ���� ���� Ÿ���� �����صΰ�,
			// ���� Ÿ���� �����մϴ�.
			HRESULT res;
			RenderTexture* renderTexture = camera->renderTexture.GetPointer();
			IDirect3DSurface9* renderSurface = nullptr;
			res = renderTexture->GetTexture()->GetSurfaceLevel(0, &renderSurface);
			res = device->SetRenderTarget(0, renderSurface);

			device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, GraphicDevice::GetInstance()->GetBackgroundColor(), 1.0f, 0);
		}
		else if (camera->overlapMode)
		{
			// ����� ����̸� ���� ���۸� �ʱ�ȭ�� ȭ�鿡 ���� �׸����� �մϴ�.

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
			// ���� �ؽ��İ� �ִ� ��쿡�� �ٽ� ���� ���� Ÿ������ �ǵ����ϴ�.

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
	// ī�޶���� �Ÿ��� ����մϴ�.
	const Vec3& cameraPosition = baseCamera->transform->position;
	for (auto& transparentRenderTarget : m_transparentRenderTargets)
	{
		auto& renderer = transparentRenderTarget.renderer;
		const Vec3& rendererPosition = renderer->transform->position;
		transparentRenderTarget.distanceFromCamera = Vec3::Distance(cameraPosition, rendererPosition);
	}

	// ī�޶���� �Ÿ��� �� ���� ����Ʈ�� �տ� ������ �����մϴ�.
	std::sort(
		m_transparentRenderTargets.begin(),
		m_transparentRenderTargets.end(),
		[](const TransparentRenderTarget& lhs, const TransparentRenderTarget& rhs)
		{
			return lhs.distanceFromCamera > rhs.distanceFromCamera;
		});

	// ���ĵ� ������ ����Ÿ���� ������� �׸��ϴ�.
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
