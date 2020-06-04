#include "RenderApplication.h"

#include <chrono>

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

RenderApplication::~RenderApplication() {}

int RenderApplication::run()
{
    // Setup resources
    if (!setup())
        return 1;

    std::chrono::high_resolution_clock hpc;
    auto start = hpc.now();

    while (m_window->isOpen())
    {
        // Receive user input
        m_window->pollEvents();

        // Draw scene
        render();

        // Swap screen buffers
        m_window->swapBuffers();

        // Time delta
        auto end = hpc.now();
        auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        dtime = ((float)diff.count()) / 1000.f;

        start = end;
    }
    return 0;
}

float RenderApplication::getTimeDelta() const { return dtime; }

unsigned int RenderApplication::getWidth() const { return m_window->getWidth(); }

unsigned int RenderApplication::getHeight() const { return m_window->getHeight(); }
