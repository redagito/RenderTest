#include "RenderApplication.h"

RenderApplication::RenderApplication()
{
	m_window = std::make_shared<Window>(800, 600, "Render Test");
	m_window->setVSync(true);
	m_window->setKeyCallback([](Window& w, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		w.close();
	}
	});
}

RenderApplication::~RenderApplication()
{
}

int RenderApplication::run()
{
	// Setup resources
	if (!setup()) return 1;

	while (m_window->isOpen())
	{
		// Receive user input
		m_window->pollEvents();

		// Draw scene
		render();

		// Swap screen buffers
		m_window->swapBuffers();
	}
	return 0;
}