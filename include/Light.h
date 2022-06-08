#pragma once

#include <gl/glew.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "Camera.h"

namespace gpr5300 {
	
	struct Light
	{
		void SetVao();
		void Draw();
		glm::vec3 coral = glm::vec3(1.0f, 0.5f, 0.31f);
		glm::vec3 lightColor = glm::vec3(0.33f, 0.42f, 0.18f);
		glm::vec3 toyColor = glm::vec3(1.0f, 0.5f, 0.31f);
		glm::vec3 result = lightColor * toyColor;
		glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
		GLuint lightvao_ = 0;
		
	};
}