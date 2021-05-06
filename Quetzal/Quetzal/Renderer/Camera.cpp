#include "Camera.h"

void Camera::UpdateCameraVectors()
{
	this->front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->front.y = sin(glm::radians(this->pitch));
	this->front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

	this->front = glm::normalize(this->front);
	this->right = glm::normalize(glm::cross(this->front, this->worldUp));
	this->up = glm::normalize(glm::cross(this->right, this->front));
}

Camera::Camera(glm::vec3 Pos, glm::vec3 WorldUp,
	float InitMovement, float InitSensitivity)
	:position(Pos), worldUp(WorldUp), up(WorldUp),
	movementSpeed(InitMovement), sensitivity(InitSensitivity),
	UpdateCamera(false)
{
	this->ViewMatrix = glm::mat4(1.f);
	this->right = glm::vec3(0.f);
	this->pitch = 45.f;
	this->yaw = 0.f;
	this->roll = 0.f;
	this->UpdateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
	this->UpdateCameraVectors();
	this->ViewMatrix = glm::lookAt(this->position, this->position + this->front, this->up);
	return this->ViewMatrix;
}

void Camera::Move(const float dt, direction Direc)
{
	glm::vec3 ChangePos = glm::vec3(this->front.x, 0.f, this->front.z);
	switch (Direc)
	{
	case direction::FORWARD:
		this->position += this->front * this->movementSpeed * dt;
		break;
	case direction::BACKWARD:
		this->position -= this->front * this->movementSpeed * dt;
		break;
	case direction::LEFT:
		this->position -= this->right * this->movementSpeed * dt;
		break;
	case direction::RIGHT:
		this->position += this->right * this->movementSpeed * dt;
		break;
	case direction::UP:
		this->position.z += 1.f * this->movementSpeed * dt;
		break;
	case direction::DOWN:
		this->position.z -= 1.f * this->movementSpeed * dt;
		break;
	default:
		break;
	}
}

void Camera::Update(float dt, const int Direc)
{
	this->UpdateCameraVectors();
}

void Camera::UpdateMouseInput(const float dt, GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		UpdateCamera = true;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		UpdateCamera = false;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		this->LastMouse = this->CurrentMouse;
	}
	if (!UpdateCamera)
		return;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		this->position += this->front * this->movementSpeed * dt;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		this->position -= this->front * this->movementSpeed * dt;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		this->position -= this->right * this->movementSpeed * dt;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		this->position += this->right * this->movementSpeed * dt;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		this->position.y +=  this->movementSpeed * dt;
	}
	//Calc offest
	glfwGetCursorPos(window, &this->CurrentMouse.X, &this->CurrentMouse.Y);
	if (this->FirstMouse)
	{
		this->LastMouse = this->CurrentMouse;
		this->FirstMouse = false;
	}
	//Calc offset
	this->MouseOffset.X = this->CurrentMouse.X - this->LastMouse.X;
	this->MouseOffset.Y = this->LastMouse.Y - this->CurrentMouse.Y;
	this->LastMouse = this->CurrentMouse;
	//Update pitch, yaw and roll
	this->pitch += static_cast<GLfloat>(this->MouseOffset.Y) * this->sensitivity * dt;
	this->yaw += static_cast<GLfloat>(this->MouseOffset.X) * this->sensitivity * dt;
	if (this->pitch > 80.f)
		this->pitch = 80.f;
	else if (this->pitch < -90.f)
		this->pitch = -89.9f;
	if (this->yaw > 360.f || this->yaw < -360.f)
		this->yaw = 0.f;
}