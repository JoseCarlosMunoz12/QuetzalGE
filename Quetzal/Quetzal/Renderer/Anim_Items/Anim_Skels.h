#pragma once
#include <iostream>
#include <vector>

#include "../Render_Items/Vertex.h"
#include "../Render_Items/Shader.h"
#include "../Render_Items/Texture.h"

struct Joint
{
	glm::vec3 Offset;
	glm::quat Rotation;
	glm::vec3 Scale;
};

class Anim_Skels
{
};

