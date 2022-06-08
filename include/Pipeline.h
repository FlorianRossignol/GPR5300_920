#pragma once
#include <iostream>
#include <gl/glew.h>
#include <glm/ext/matrix_float4x4.hpp>
#include "scene.h"
#include "Camera.h"
#include "file_utility.h"

namespace gpr5300
{
	class Pipeline
	{
	public:
		Pipeline();
		void Load(std::string_view Vertex_path,std::string_view Fragment_path);
		void Delete();
		void SetMatrix(glm::mat4 &model, std::string_view model_name) const;
		void SetInt(std::string_view uniform_name,int value);
		void SetVec3(std::string_view uniform_name, glm::vec3 value);
		
	private:
		GLuint vertexShader_=0;
		GLuint fragmentShader_ = 0;
		GLuint pipeline_ = 0;
	};

}
