#include "Shader.h"
#include "glm/gtc/type_ptr.hpp"

namespace gpr5300
{
	Shader::Shader() = default;
	

	void Shader::Load(std::string_view Vertex_path, std::string_view Fragment_path)
	{
		const auto vertexContent = LoadFile(Vertex_path);
		const auto* ptr = vertexContent.data();
		vertexShader_ = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader_, 1, &ptr, nullptr);
		glCompileShader(vertexShader_);

		GLint sucess;
		glGetShaderiv(vertexShader_, GL_COMPILE_STATUS, &sucess);

		if (!sucess)
		{
			std::cerr << "Error while loading vertex Shader\n";
		}

		const auto fragmentContent = LoadFile(Fragment_path);
		ptr = fragmentContent.data();
		fragmentShader_ = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader_, 1, &ptr, nullptr);
		glCompileShader(fragmentShader_);
		char infoLog[512];
		glGetShaderiv(fragmentShader_, GL_COMPILE_STATUS, &sucess);
		if (!sucess)
		{
			glGetProgramInfoLog(pipeline_, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::FRAGMENTSHADER::LINKING_FAILED\n" << infoLog << std::endl;
		}
		pipeline_ = glCreateProgram();
		glAttachShader(pipeline_, vertexShader_);
		glAttachShader(pipeline_, fragmentShader_);
		glLinkProgram(pipeline_);

		
		glGetProgramiv(pipeline_, GL_LINK_STATUS, &sucess);
		if (!sucess)
		{
			glGetProgramInfoLog(pipeline_, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::VERTEXSHADER::LINKING_FAILED\n" << infoLog << std::endl;
		}
		
		glUseProgram(pipeline_);
	}


	void Shader::Delete()
	{
		glDeleteProgram(pipeline_);
		glDeleteShader(vertexShader_);
		glDeleteShader(fragmentShader_);
	}

	void Shader::SetMatrix(glm::mat4 &model,std::string_view model_name) const
	{
		const int modelLock = glGetUniformLocation(pipeline_, model_name.data());
		glUniformMatrix4fv(modelLock, 1, GL_FALSE, glm::value_ptr(model));
	}

	void Shader::SetInt(std::string_view uniform_name,int value)
	{
		glUniform1i(glGetUniformLocation(pipeline_, uniform_name.data()), value);
	}
	void Shader::SetVec3(const std::string_view &uniform_name, float x, float y, float z)
	{
		glUniform3f(glGetUniformLocation(pipeline_, uniform_name.data()),x,y,z);
	}

	void Shader::SetVec3(const std::string_view &uniform_name, const glm::vec3& value)
	{
		glUniform3fv(glGetUniformLocation(pipeline_, uniform_name.data()), 1, &value[0]);
	}

	void Shader::SetFloat(const std::string_view& uniform_name, float number)
	{
		glUniform1f(glGetUniformLocation(pipeline_, uniform_name.data()), number);
	}


	void Shader::Use()
	{
		glUseProgram(pipeline_);
	}
}
