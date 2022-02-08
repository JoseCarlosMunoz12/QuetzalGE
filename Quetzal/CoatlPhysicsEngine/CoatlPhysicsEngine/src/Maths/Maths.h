#pragma once
#include "../define.h"
#include <vector>
namespace CoatlPhysicsEngine
{
	class COATL_API VectorXD
	{
	protected:
		std::vector<double> Vecs;
	public:
		VectorXD(int initSize);
		VectorXD(int initSize, double initVal);
	};
	class COATL_API Vector3D : public VectorXD
	{
	private:
	public:
		Vector3D();
		Vector3D(double initVal);
		Vector3D(double initX, double initY, double initZ);
	};
}