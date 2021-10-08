#pragma once

#include "MaterialParameters.h"

class Material;
class Renderer;
class Camera;

struct TransparentRenderTarget
{
	float distanceFromCamera;
	Renderer* renderer;
};

class RenderProcess
{
public:

	RenderProcess();

	~RenderProcess();

	void ClearRenderTargets();

	void AddRenderTarget(Renderer* renderer);

	void Process();

private:

	void Render(Camera* baseCamera);

	void RenderTo(Camera* baseCamera, RenderQueue renderQueue);

	void RenderTransparent(Camera* baseCamera);

	void RenderOverlay(Camera* baseCamera);

	void SortOverlay();

private:

	using RendererList = std::list<Renderer*>;

	using RenderTargetMap = std::unordered_map<Material*, RendererList>;

	using TransparentRenderVector = std::vector<TransparentRenderTarget>;

	using OverlayRenderVector = std::vector<Renderer*>;

	// ���������� ���� �������� ���Ǵ� ���� �����Դϴ�.
	RenderTargetMap m_renderTargets[unsigned int(RenderQueue::Max)];

	// �������� �������� ���Ǵ� ���� �����Դϴ�.
	TransparentRenderVector m_transparentRenderTargets;

	// �������� �������� ���Ǵ� ���� �����Դϴ�.
	OverlayRenderVector m_overlayRenderTargets;

	Material* m_initMaterial = nullptr;
};

