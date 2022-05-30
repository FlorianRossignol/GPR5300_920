#pragma once
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "SDL2/SDL.h"

namespace gpr5300
{
	struct Camera
	{
		 glm::mat4 projection_ = glm::mat4(1.0f);
		 glm::mat4 model_ = glm::mat4(1.0f);
		 glm::mat4 view_ = glm::mat4(1.0f);
		 glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		 glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		 glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraFront);
		 glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		 glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
		 glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		
		 void SetCamera(const float tt);
		 void ProcessInput(float);
	};
}
