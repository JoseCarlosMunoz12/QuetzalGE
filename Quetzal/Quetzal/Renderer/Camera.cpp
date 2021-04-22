#include "Camera.h"


void Camera::UpdateCameraVectors()
{

	this->front.x = -cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->front.z = sin(glm::radians(this->pitch));
	this->front.y = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

	this->front = glm::normalize(this->front);
	this->right = glm::normalize(glm::cross(this->front, this->worldUp));
	this->up = glm::normalize(glm::cross(this->right, this->front));
}

Camera::Camera(glm::vec3 Pos, glm::vec3 WorldUp,
	float InitMovement, float InitSensitivity)
	:position(Pos),worldUp(WorldUp),up(WorldUp),
	movementSpeed(InitMovement), sensitivity(InitSensitivity)
{
	this->ViewMatrix = glm::mat4(1.f);
	this->right = glm::vec3(0.f);
	this->up = worldUp;
	this->pitch = 0.f;
	this->yaw = 0.f;
	this->roll = 0.f;
	this->UpdateCameraVectors();
}

void Camera::Update(float dt, const int Direc)
{
	Direc;
}
