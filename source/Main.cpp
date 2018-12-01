#include <iostream>

#include "Window.h"
#include "Buffer.h"
#include "Shader.h"
#include "ShaderCode.h"

int guardedMain(int argc, char** argv)
{
	Window window{800, 600, "Render Test"};
	window.setVSync(true);
	window.setKeyCallback([](Window& w, int key, int scancode, int action, int mods) {
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			w.close();
		}
	});

	// Vertices
	static const GLfloat vertices[][2] = {
		{-0.9f, -0.9f},
		{0.85f, -0.9f},
		{-0.9f, 0.85f},
		{0.9f, -0.85f},
		{0.9f, 0.9f},
		{-0.85f, 0.9f}
	};

	Buffer vertexBuffer;
	vertexBuffer.setData((GLfloat*)vertices, sizeof(vertices) / sizeof(GLfloat), GL_STATIC_DRAW);

	// Vertex array object
	GLuint vertexArray;
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	auto shader = createShaderProgram(vertexCode, fragmentCode);

	while (window.isOpen())
	{
		window.pollEvents();

		// Clear color buffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader);

		// Draw
		glEnableVertexAttribArray(0);
		vertexBuffer.bind(0, GL_ARRAY_BUFFER);

		glDrawArrays(GL_TRIANGLES, 0, vertexBuffer.getCount() / 3);
		glDisableVertexAttribArray(0);

		// Swap screen buffers
		window.swapBuffers();
	}

	return 0;
}

int main(int argc, char **argv) {
	try
	{
		return guardedMain(argc, argv);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}