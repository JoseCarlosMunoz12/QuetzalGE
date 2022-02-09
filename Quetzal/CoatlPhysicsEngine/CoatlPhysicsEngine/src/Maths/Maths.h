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
		double& operator[] (int id) { return Vecs[id]; }
	};
	class COATL_API Vector3D : public VectorXD
	{
	private:
	public:
		Vector3D();
		Vector3D(double initVal);
		Vector3D(double initX, double initY, double initZ);
	};
	class COATL_API MatrixXxYD
	{
	private:
		std::vector<VectorXD> Rows;
	public:
		MatrixXxYD(int initRC);
		MatrixXxYD(int initRows, int initCols);
		MatrixXxYD(int initRows, int initCols, double initVal);
		VectorXD& operator[](int ID) { return Rows[ID]; };
	};
}