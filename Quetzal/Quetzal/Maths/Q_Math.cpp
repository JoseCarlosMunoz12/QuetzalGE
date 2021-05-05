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
