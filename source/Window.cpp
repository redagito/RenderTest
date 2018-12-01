#include "Window.h"

#include <stdexcept>

Window* Window::s_window = nullptr;

Window::Window(unsigned int width, unsigned int height, const char* title)
{
	if (s_window != nullptr)
	{
		throw std::runtime_error{"Only single window allowed"};
	}
	s_window = this;

	// Init glfw
	if (glfwInit() != GLFW_TRUE) {
		throw std::runtime_error{ "Failed to init glfw" };
	}

	// Setup error callback
	glfwSetErrorCallback([](int code, const char* error) {
		throw std::runtime_error{ error };
	});

	// Setup for Opengl context
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	// Create window
	m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (m_window == nullptr)
	{
		glfwTerminate();
		throw std::runtime_error{ "Failed to create window" };
	}

	// Key callback
	glfwSetKeyCallback(m_window, [](GLFWwindow* w, int key, int code, int action, int mods) {
		if (Window::s_window == nullptr) return;
		Window::s_window->m_keyCallback(*Window::s_window, key, code, action, mods);
	});

	// Set active context
	glfwMakeContextCurrent(m_window);

	// Load opengl functions
	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0)
	{
		throw std::runtime_error{ "Failed to init GL context" };
	}

	// Initial viewport is the entire window
	glViewport(0, 0, width, height);
}

Window::~Window()
{
	if (m_window != nullptr)
	{
		glfwDestroyWindow(m_window);
	}
	glfwTerminate();
	s_window = nullptr;
}

void Window::swapBuffers()
{
	glfwSwapBuffers(m_window);
}

void Window::setVSync(bool sync)
{
	if (sync) {
		glfwSwapInterval(1);
	}
	else {
		glfwSwapInterval(0);
	}
}

void Window::pollEvents()
{
	glfwPollEvents();
}

void Window::close()
{
	glfwSetWindowShouldClose(m_window, GLFW_TRUE);
}

void Window::setKeyCallback(const KeyCallback & callback)
{
	m_keyCallback = callback;
}

bool Window::isOpen() const
{
	return glfwWindowShouldClose(m_window) == GLFW_FALSE;
}

int Window::getKey(int code) const
{
	return glfwGetKey(m_window, code);
}