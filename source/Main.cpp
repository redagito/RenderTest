#include <iostream>

#include "ShaderCode.h"
#include "RenderApplication.h"

class App1 : public RenderApplication
{
private:
	Buffer m_vertexBuffer;
	GLuint m_shader = 0;

	bool setup() override
	{
		// Vertices
		static const GLfloat vertices[][2] = {
			{-0.9f, -0.9f},
			{0.85f, -0.9f},
			{-0.9f, 0.85f},
			{0.9f, -0.85f},
			{0.9f, 0.9f},
			{-0.85f, 0.9f}
		};

		m_vertexBuffer.setData((GLfloat*)vertices, sizeof(vertices) / sizeof(GLfloat), 0);

		// Vertex array object
		GLuint vertexArray;
		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);

		m_shader = createShaderProgram(vertexCode, fragmentCode);
		return true;
	}

	void render() override
	{
		// Clear color buffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(m_shader);

		// Draw
		glEnableVertexAttribArray(0);
		m_vertexBuffer.bind(0, GL_ARRAY_BUFFER);

		glDrawArrays(GL_TRIANGLES, 0, m_vertexBuffer.getCount() / 3);
		glDisableVertexAttribArray(0);
	}

public:
	~App1()
	{
		glDeleteProgram(m_shader);

	}
};

int guardedMain(int argc, char** argv)
{
	App1 app;
	return app.run();
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