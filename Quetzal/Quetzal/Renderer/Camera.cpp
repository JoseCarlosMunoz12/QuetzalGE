#include "Camera.h"


Camera::Camera(glm::vec3 Pos, glm::vec3 WorldUp,
	float InitMovement, float InitSensitivity)
	:position(Pos),worldUp(WorldUp),movementSpeed(InitMovement), sensitivity(InitSensitivity)
{
}

void Camera::Update(float dt, const int Direc)
{
	Direc;
}
