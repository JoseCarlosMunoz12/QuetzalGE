#include "Maths.h"
using namespace CoatlPhysicsEngine;

VectorXD::VectorXD(int initSize)
{
	for (int ii = 0; ii < initSize; ii++)
		this->Vecs.push_back(0.f);
}

VectorXD::VectorXD(int initSize, double initVal)
{
	for (int ii = 0; ii < initSize; ii++)
		this->Vecs.push_back(initVal);

}

Vector3D::Vector3D()
	:VectorXD(3)
{
}

Vector3D::Vector3D(double initVal)
	: VectorXD(3, initVal)
{
}

Vector3D::Vector3D(double initX, double initY, double initZ)
	:VectorXD(3)
{

}
