#include "Q_Math.h"

void Math::Decompose(glm::mat4 Transform, glm::vec3& Translation, glm::quat& Rotation, glm::vec3& Scale)
{
	//Getting Translation
	Translation = Decompose_Trns(Transform);
	//Getting Scale
	Scale = Decompose_Scl(Transform);
	//Get Rotation
	Rotation = Decompose_Rt(Transform);
}

glm::vec3 Math::Decompose_Trns(glm::mat4 Transform)
{
	return Transform[3];
}

glm::vec3 Math::Decompose_Scl(glm::mat4 Transform)
{
	glm::vec3 Row[3];
	for (int ii = 0; ii < 3; ii++)
		for (int jj = 0; jj < 3; jj++)
			Row[ii][jj] = Transform[ii][jj];
	glm::vec3 Scale;
	Scale.x = glm::length(Row[0]);
	Scale.y = glm::length(Row[1]);
	Scale.z = glm::length(Row[2]);
	return Scale;
}

glm::quat Math::Decompose_Rt(glm::mat4 Transform)
{
	glm::vec3 r = Decompose_Scl(Transform);
	//Transform Column 1
	Transform[0][0] = Transform[0][0] / r.x;
	Transform[0][1] = Transform[0][1] / r.x;
	Transform[0][2] = Transform[0][2] / r.x;
	//Transform Column 2
	Transform[1][0] = Transform[1][0] / r.y;
	Transform[1][1] = Transform[1][1] / r.y;
	Transform[1][2] = Transform[1][2] / r.y;
	//Transform Column 3
	Transform[2][0] = Transform[2][0] / r.z;
	Transform[2][1] = Transform[2][1] / r.z;
	Transform[2][2] = Transform[2][2] / r.z;
	glm::vec3 Row[3];
	for (int ii = 0; ii < 3; ii++)
		for (int jj = 0; jj < 3; jj++)
			Row[ii][jj] = Transform[ii][jj];
	//Get Rotation
	int i = 0, j = 0, k = 0;
	float root = 0;
	float trace = Row[0].x + Row[1].y + Row[2].z;
	glm::quat Orientation;
	if (trace > 0)
	{
		root = glm::sqrt(trace + 1.f);
		Orientation.w = .5f * root;
		root = .5f / root;
		Orientation.x = root * (Row[1].z - Row[2].y);
		Orientation.y = root * (Row[2].x - Row[0].z);
		Orientation.z = root * (Row[0].y - Row[1].x);
	}
	else
	{
		static int Next[3] = { 1,2,0 };
		i = 0;
		if (Row[1].y > Row[0].x) i = 1;
		if (Row[2].z > Row[i][i]) i = 2;
		j = Next[i];
		k = Next[j];

		root = glm::sqrt(Row[i][i] - Row[k][k]);

		Orientation[i] = .5f * root;
		root = .5f / root;
		Orientation[j] = root * (Row[i][j] + Row[j][i]);
		Orientation[k] = root * (Row[i][k] + Row[k][i]);
		Orientation.w = root * (Row[j][k] + Row[k][j]);
	}
	return Orientation;
}

glm::vec3 Math::Quat_To_Eulor(glm::quat Quat)
{
	glm::vec3 angles;
	// roll (z-axis rotation)
	double sinr_cosp = 2 * (Quat.w * Quat.x + Quat.y * Quat.z);
	double cosr_cosp = 1 - 2 * (Quat.x * Quat.x + Quat.y * Quat.y);
	angles.z = std::atan2(sinr_cosp, cosr_cosp);

	// pitch (x-axis rotation)
	double sinp = 2 * (Quat.w * Quat.y - Quat.z * Quat.x);
	if (std::abs(sinp) >= 1)
		angles.x = std::copysign(glm::pi<float>() / 2, sinp); // use 90 degrees if out of range
	else
		angles.x = std::asin(sinp);

	// yaw (y-axis rotation)
	double siny_cosp = 2 * (Quat.w * Quat.z + Quat.x * Quat.y);
	double cosy_cosp = 1 - 2 * (Quat.y * Quat.y + Quat.z * Quat.z);
	angles.y = std::atan2(siny_cosp, cosy_cosp);
	return (180 / glm::pi<float>()) * angles;
}

glm::quat Math::Eulor_To_Quat(glm::vec3 Eulor)
{
	Eulor = (glm::pi<float>() / 180.f) * Eulor;
	// Abbreviations for the various angular functions
	double cy = cos(Eulor.y * 0.5);
	double sy = sin(Eulor.y * 0.5);
	double cp = cos(Eulor.x * 0.5);
	double sp = sin(Eulor.x * 0.5);
	double cr = cos(Eulor.z * 0.5);
	double sr = sin(Eulor.z * 0.5);

	glm::quat q;
	q.w = cr * cp * cy + sr * sp * sy;
	q.x = sr * cp * cy - cr * sp * sy;
	q.y = cr * sp * cy + sr * cp * sy;
	q.z = cr * cp * sy - sr * sp * cy;

	return q;;
}
