#pragma once

#include <memory>

#include "Window.h"

/**
 * Provides basic rendering context and window creation.
 */
class RenderApplication
{
   public:
    RenderApplication();
    virtual ~RenderApplication();

    int run();

   protected:
    // Delta time in seconds
    float getTimeDelta() const;

   private:
    std::shared_ptr<Window> m_window;
    float dtime = 0.f;

    virtual bool setup() = 0;
    virtual void render() = 0;
};