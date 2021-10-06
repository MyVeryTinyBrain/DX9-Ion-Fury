#pragma once

#include "MaterialParameters.h"

class Renderer;

class RenderProcess
{
public:

	void AddRenderTarget(Renderer* renderer);

private:

	std::vector<Renderer*> m_renderTargets[unsigned int(RenderQueue::Max)];
};

