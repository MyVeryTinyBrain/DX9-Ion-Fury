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

	// 반투명하지 않은 렌더링에 사용되는 렌더 대상들입니다.
	RenderTargetMap m_renderTargets[unsigned int(RenderQueue::Max)];

	// 반투명한 렌더링에 사용되는 렌더 대상들입니다.
	TransparentRenderVector m_transparentRenderTargets;

	// 오버레이 렌더링에 사용되는 렌더 대상들입니다.
	OverlayRenderVector m_overlayRenderTargets;

	Material* m_initMaterial = nullptr;
};

