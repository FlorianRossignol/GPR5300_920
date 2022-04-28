#include <fstream>
#include <iostream>
#include <sstream>
#include <GL/glew.h>

#include "engine.h"
#include "file_utility.h"
#include "scene.h"

namespace gpr5300
{
	class EboTest final : public Scene
	{
	public:
		void Begin() override;
		void End() override;
		void Update(float dt) override;
	private:
		GLuint vertexShader = 0;
		GLuint fragmentShader_ = 0;
		GLuint program_ = 0;
		GLuint vao_ = 0;
		GLuint vbo_[2] = {};
		GLuint ebo_ = 0;
		float t = 0.0f;
	};
	
	float vertices[12] = {
		0.5f,0.5f,0.0f,
		0.5f,0.5f,0.0f,
		-0.5f,-0.5f,0.0f,
		-0.5f,0.0f,0.5f
	};
	float colors[12] =	{
		1.0f,0.0f,1.0f,
		0.0f,1.0f,0.0f,
		0.0f,0.0f,1.0f,
		0.5f,0.0f,0.5f
	};
	unsigned int indices[6] = {
		0,1,3,
		1,2,3
	};

	void EboTest::Begin()
	{
		//ebo
		glGenBuffers(1, &ebo_);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		//vbo
		glGenBuffers(1, &vbo_[0]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glGenBuffers(1, &vbo_[1]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, ebo_);

		//vao
		glGenVertexArrays(1, &vao_);
		glBindVertexArray(vao_);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_[0]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_[1]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);

		//shader
		const auto vertexContent = LoadFile("data/shaders/hello_triangle/triangle.vert");
		const auto* ptr = vertexContent.data();
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &ptr, nullptr);
		glCompileShader(vertexShader);


		GLint sucess;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &sucess);
		if (!sucess)
		{
			std::cerr << "Error while loading vertex shader\n";
		}
		const auto fragmentContent = LoadFile("data/shaders/hello_triangle/triangle.frag");
		ptr = fragmentContent.data();
		fragmentShader_ = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader_, 1, &ptr, nullptr);
		glCompileShader(fragmentShader_);

		glGetShaderiv(fragmentShader_, GL_COMPILE_STATUS, &sucess);
		if (!sucess)
		{
			std::cerr << "Error while loading fragment shader\n";
		}

		program_ = glCreateProgram();
		glAttachShader(program_, vertexShader);
		glAttachShader(program_, fragmentShader_);
		glLinkProgram(program_);


		glGetProgramiv(program_, GL_LINK_STATUS, &sucess);
		if (!sucess)
		{
			std::cerr << "Error while linking shader program\n";
		}

	}

	void EboTest::End()
	{
		glDeleteProgram(program_);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader_);
		glDeleteVertexArrays(1, &vao_);
	}

	void EboTest::Update(float dt)
	{
		t += dt;
		glUseProgram(program_);
		const float colorValue = (std::cos(t + 4.5f));
		glUniform1f(glGetUniformLocation(program_, "colorCoeff"), colorValue);
		glBindVertexArray(vao_);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}

}

int main(int argc, char** argv)
{
	gpr5300::EboTest scene;
	gpr5300::Engine engine(&scene);
	engine.Run();
	return EXIT_SUCCESS;
}