#pragma once

#include <glad/glad.h>
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
private:
	KeyCallback m_keyCallback;
	GLFWwindow* m_window;

	static Window* s_window;
};