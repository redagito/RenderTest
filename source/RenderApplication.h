#pragma once

#include <memory>

#include "Window.h"
#include "Buffer.h"
#include "Shader.h"

/**
* Provides basic rendering context and window creation.
*/
class RenderApplication
{
public:
	RenderApplication();
	virtual ~RenderApplication();

	int run();

private:
	std::shared_ptr<Window> m_window;

	virtual bool setup() = 0;
	virtual void render() = 0;
};