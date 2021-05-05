#pragma once
#include <glm.hpp>
#include "gtc/matrix_transform.hpp"
#include "gtc/quaternion.hpp"
//Math Library for Quetzal Renderer
namespace Math
{
	//matrix decomposition
	void Decompose(glm::mat4 Transform, glm::vec3& Translation, glm::quat& Rotation, glm::vec3& Scale);
	glm::vec3 Decompose_Trns(glm::mat4 Transform);
	glm::vec3 Decompose_Scl(glm::mat4 Transform);
	glm::quat Decompose_Rt(glm::mat4 Transform);
	//Eulor to Quaternions and Vice versa
	glm::vec3 Quat_To_Eulor(glm::quat Quat);
	glm::quat Eulor_To_Quat(glm::vec3 Eulor);
}