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

	void ClearRenderTargets();

	void AddRenderTarget(Renderer* renderer);

	void Process();

private:

	void Render(Camera* baseCamera);

	void RenderTo(Camera* baseCamera, RenderQueue renderQueue);

	void RenderTransparent(Camera* baseCamera);

private:

	using RendererList = std::list<Renderer*>;

	using RenderTargetMap = std::unordered_map<Material*, RendererList>;

	using TransparentRenderVector = std::vector<TransparentRenderTarget>;

	// ���������� ���� �������� ���Ǵ� ���� �����Դϴ�.
	RenderTargetMap m_renderTargets[unsigned int(RenderQueue::Max)];

	// �������� �������� ���Ǵ� ���� �����Դϴ�.
	TransparentRenderVector m_transparentRenderTargets;
};

