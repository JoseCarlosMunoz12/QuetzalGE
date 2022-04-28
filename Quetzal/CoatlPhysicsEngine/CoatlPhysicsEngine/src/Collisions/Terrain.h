#pragma once
#include "../define.h"
#include "../OptimizaAlgorithm/OctoTree.h"
#include "../Shapes/AABB_Obj.h"
#include "../Shapes/Triangles.h"
namespace CoatlPhysicsEngine
{
	class COATL_API Terrain
	{
	private:
		std::unique_ptr<OctoTree> TerWorld;
	public:
		Terrain(std::vector<glm::vec3> Mesh, std::vector<int> Index,float Dim);
		~Terrain();
		std::vector<std::shared_ptr<Bodies>> GetTerrs(glm::vec3 Pos, float Ext);
	};

}