#pragma once
#include "../define.h"
#include <vector>
namespace CoatlPhysicsEngine
{
	class COATL_API VectorXD
	{
	private:
		std::vector<double> Vecs;
	public:
		VectorXD(int initSize);
		VectorXD(int initSize, double initVal);
	};
}