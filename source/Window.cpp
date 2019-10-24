#include "Window.h"

#include <stdexcept>
#include <iostream>

static void APIENTRY glDebugOutput(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	// ignore non-significant error/warning codes
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	std::cout << "---------------" << std::endl;
	std::cout << "Debug message (" << id << "): " << message << std::endl;

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
	case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
	} std::cout << std::endl;

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
	case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
	case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
	} std::cout << std::endl;

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
	case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
	case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
	} std::cout << std::endl;
	std::cout << std::endl;
}

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
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	
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

	// Setup debug vallback
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(glDebugOutput, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

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