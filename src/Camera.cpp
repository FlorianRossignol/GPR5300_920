#include "Camera.h"
#include <Windows.h>
#include "error.h"

namespace gpr5300
{
	void Camera::OnEvent(const SDL_Event& event)
	{
		SDL_GetMouseState(&mousePosx, &mousePosy);
		switch (event.type)
		{
		case SDL_MOUSEMOTION:
			mouseCallback(mousePosx, mousePosy);
			ProcessMouseMovement(event.motion.xrel, event.motion.yrel);
			break;
		default:
			break;
		}
	}

	void Camera::SetCamera(const float tt)
	{
		view_ = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp_);
		constexpr float radius = 10.0f;
		const float camX = sin(tt * radius);
		const float camZ = cos(tt * radius);
		view_ = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	}

	void Camera::ProcessInput(float dt)
	{
		const auto camera_speed = static_cast<float>(1.0f * dt);
		const Uint8* state = SDL_GetKeyboardState(nullptr);

		if (state[SDL_SCANCODE_W])
		{
			cameraPos += camera_speed * cameraFront;
		}
		if (state[SDL_SCANCODE_S])
		{
			cameraPos -= camera_speed * cameraFront;
		}
		if (state[SDL_SCANCODE_A])
		{
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp_)) * camera_speed;
		}
		if (state[SDL_SCANCODE_D])
		{
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp_)) * camera_speed;
		}

	}

	void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
	{
		xoffset *= MouseSensitivity_;
		yoffset *= MouseSensitivity_;

		Yaw_ += xoffset;
		Pitch_ += yoffset;

		if (constrainPitch)
		{
			if (Pitch_ > 89.0f)
			{
				Pitch_ = 89.0f;
			}
			if (Pitch_ < -89.0f)
			{
				Pitch_ = -89.0f;
			}
		}
		cameraFront.x = std::cos(glm::radians(Yaw_)) * std::cos(glm::radians(Pitch_));
		cameraFront.y = std::sin(glm::radians(Pitch_));
		cameraFront.z = std::sin(glm::radians(Yaw_)) * std::cos(glm::radians(Pitch_));
		cameraFront = glm::normalize(cameraFront);
		// also re-calculate the Right and Up vector
		cameraRight_ = glm::normalize(glm::cross(cameraFront, worldUp_));// normalize the vectors, because their length gets closer to 0 the more you look up_ or down which results in slower movement.
		cameraUp_ = glm::normalize(glm::cross(cameraRight_, cameraFront));
	}

	void Camera::ProcessMouseScroll(float yoffset)
	{
		zoom_ -= (float)yoffset;
		if (zoom_ < 1.0f)
			zoom_ = 1.0f;
		if (zoom_ > 45.0f)
			zoom_ = 45.0f;
	}

	void Camera::mouseCallback(float xposIn, float yposIn)
	{

		float xpos = static_cast<float>(xposIn);
		float ypos = static_cast<float>(yposIn);

		if (firstMouse)
		{
			lastx = xpos;
			lasty = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastx;
		float yoffset = lasty - ypos; // reversed since y-coordinates go from bottom to top

		lastx = xpos;
		lasty = ypos;

		ProcessMouseMovement(xoffset, yoffset);

	}

	glm::mat4 Camera::GetViewMatrix()
	{
		return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp_);
	}

}
