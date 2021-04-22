#pragma once
#include <iostream>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <vec3.hpp>
#include <mat4x4.hpp>
#include <gtc\type_ptr.hpp>
#include "Render_Items/Vertex.h"

enum class direction {
	FORWARD = 0,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};
class Camera
{
private:

	GLfloat movementSpeed;
	GLfloat sensitivity;

	glm::vec3 worldUp;
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;

	GLfloat pitch;
	GLfloat yaw;
	GLfloat roll;

	glm::mat4 ViewMatrix;
public:
	Camera(glm::vec3 Pos, glm::vec3 WorldUp,
		float InitMovement = 3.f, float InitSensitivity = 5.f);
	~Camera() {}
	//Getters
	glm::vec3 GetPos() { return this->position; }
	glm::mat4 GetViewMatrix() { return this->ViewMatrix; }
	//Setters
	void SetPosition(glm::vec3 NewPos) { this->position = NewPos; }
	float GetMovementSpeed()           { return this->movementSpeed; }
	float GetSensitivity()             { return this->sensitivity; }
	//update matrices
	void Update(float dt, const int Direc);
};