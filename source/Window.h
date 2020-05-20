#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>

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

   private:
    KeyCallback m_keyCallback = nullptr;
    GLFWwindow* m_window = nullptr;

    static Window* s_window;
};