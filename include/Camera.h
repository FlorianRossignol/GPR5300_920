#pragma once
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "SDL2/SDL.h"
#include "engine.h"

namespace gpr5300
{
	enum Camera_Movement
	{
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};
	constexpr  float YAW = -90.0f;
	constexpr  float PITCH = 0.0f;
	constexpr  float SPEED = 2.5f;
	constexpr  float SENSITIVITY = 0.1f;
	constexpr  float ZOOM = 45.0f;

	struct Camera
	{
	public:
		 glm::mat4 model_ = glm::mat4(1.0f);
		 glm::mat4 view_;
		 glm::vec3 cameraPos;
		 glm::vec3 cameraFront;
		 glm::vec3 cameraRight_;
		 glm::vec3 cameraUp_;
		 glm::vec3 worldUp_;
		 float MovementSpeed_;
		 float MouseSensitivity_;
		 float zoom_;
		 float Yaw_;
		 float Pitch_;
		 int mousePosy = 0;
		 int mousePosx = 0;
		 bool firstMouse = true;
		 const unsigned int SCR_WIDTH = 1920;
		 const unsigned int SCR_HEIGHT = 1080;
		 float lastx = SCR_WIDTH / 2.0f;
		 float lasty = SCR_HEIGHT / 2.0f;
		 Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed_(SPEED), MouseSensitivity_(SENSITIVITY), zoom_(ZOOM)
		 {
		 	cameraPos = position;
			 worldUp_ = up;
			 Yaw_ = yaw;
			 Pitch_ = pitch;
		 }
		 Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed_(SPEED), MouseSensitivity_(SENSITIVITY), zoom_(ZOOM)
		 {
			 cameraPos = glm::vec3(posX, posY, posZ);
			 worldUp_ = glm::vec3(upX, upY, upZ);
			 Yaw_ = yaw;
			 Pitch_ = pitch;
		 }
		 void OnEvent(const SDL_Event& event);
		 void SetCamera(const float tt);
		 void ProcessInput(float dt);
		 void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
		 void ProcessMouseScroll(float yoffset);
		 void mouseCallback(float xposIn, float yposIn);
		 glm::mat4 GetViewMatrix();
	};
}
