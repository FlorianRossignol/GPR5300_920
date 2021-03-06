#pragma once
#include <iostream>
#include <gl/glew.h>
#include <glm/ext/matrix_float4x4.hpp>
#include "scene.h"
#include "Camera.h"
#include "file_utility.h"

namespace gpr5300
{
	class Shader
	{
	public:
		Shader();
		void Load(std::string_view Vertex_path,std::string_view Fragment_path);
		void Delete();
		void SetMatrix(glm::mat4 &model, std::string_view model_name) const;
		void SetInt(std::string_view uniform_name,int value);
		void SetVec3(const std::string_view &uniform_name, float x,float y, float z);
		void SetVec3(const std::string_view &uniform_name, const glm::vec3& value);
		void SetFloat(const std::string_view& uniform_name, float number);
		void Use();
		unsigned int ID;
		
	private:
		GLuint vertexShader_=0;
		GLuint fragmentShader_ = 0;
		GLuint pipeline_ = 0;
	};

}
	