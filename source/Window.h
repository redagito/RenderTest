#pragma once

#include <glad/glad.h>
// GLAD include first
#include <GLFW/glfw3.h>

class Window
{
   public:
    Window(unsigned int width, unsigned int height, const char* title);
    ~Window();

    using KeyCallback = void (*)(Window&, int, int, int, int);

    void swapBuffers();

    void setVSync(bool sync);

    void pollEvents();

    void close();

    void setKeyCallback(const KeyCallback& callback);

    bool isOpen() const;

    int getKey(int code) const;

    unsigned int getWidth() const;
    unsigned int getHeight() const;

   private:
    void onResize(unsigned int width, unsigned int height);

    unsigned int m_width = 0;
    unsigned int m_height = 0;
    KeyCallback m_keyCallback = nullptr;
    GLFWwindow* m_window = nullptr;

    static Window* s_window;
};