#include "Camera.h"
#include <Windows.h>

namespace gpr5300
{
	 void Camera::SetCamera(const float tt)
	{
	 	view_ = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	 	const float radius = 10.0f;
		float camX = sin(tt * radius);
		float camZ = cos(tt * radius);
		view_ = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	}

	 void Camera::ProcessInput(float dt)
	 {
		const auto camera_speed = static_cast<float>(1.0f * dt);
		
		 if (SDL_GetKeyFromName("W") == SDL_KEYDOWN)
		 {	
			 cameraPos += camera_speed * cameraFront;
		 }
		 if (SDL_GetKeyFromName("S") == SDL_KEYDOWN)
		 {
			 cameraPos -= camera_speed * cameraFront;
		 }
		 if (SDL_GetKeyFromName("A") == SDL_KEYDOWN)
		 {
			 cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * camera_speed;
		 }
		 if (SDL_GetKeyFromName("D") == SDL_KEYDOWN)
		 {
			 cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * camera_speed;
		 }
	 }
}