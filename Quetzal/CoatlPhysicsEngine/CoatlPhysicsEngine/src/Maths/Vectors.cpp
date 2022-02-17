#include "Vectors.h"
using namespace CoatlPhysicsEngine;

///
///VectorXD
///

VecXD::VecXD(int Size, double InitVal)
{
	for (int ii = 0; ii < Size; ii++)
		Vec.push_back(InitVal);
}

int VecXD::Size()
{
	return Vec.size();
}

double VecXD::length()
{
	double sqr = 0.f;
	for (auto& jj : Vec)
		sqr += pow(jj, 2);
	return sqrt(sqr);
}

void VecXD::Normalize()
{
	double lngth = length();
	for (auto& jj : Vec)
	{
		jj = jj / lngth;
	}
}

void VecXD::Multiply(double f)
{
	int size = Size();
	for (int ii = 0; ii < size; ii++)
		Vec[ii] = f * Vec[ii];
}

std::string VecXD::GetStr()
{
	int size = Size();
	std::string str = "[";
	for (int ii = 0; ii < size; ii++)
		str += " " + std::to_string(Vec[ii]);
	return str + " ]\n";
}

///
///Vector3D
///

Vec3D::Vec3D()
	:VecXD(3, 0.f)
{
}

Vec3D::Vec3D(double init)
	: VecXD(3, init)
{
}

Vec3D::Vec3D(double x, double y, double z)
	: VecXD(3, x)
{
	(*this)[1] = y;
	(*this)[2] = z;
}

void Vec3D::Display()
{
	std::cout << "X:" << (*this)[0] << ",";
	std::cout << "Y:" << (*this)[1] << ",";
	std::cout << "Z:" << (*this)[2] << "\n";
}

///
///Quat
///

double Quat::sgn(double x)
{
	return copysignf(1.f, x);
}

double Quat::f32_mma(double a, double b, double c, double d)
{
	double t = c * d;
	double e = fmaf(c, d, -t);
	double f = fmaf(a, b, t);
	return f + e;
}

double Quat::f32_mms(double a, double b, double c, double d)
{
	double t = c * d;
	double e = fmaf(c, d, -t);
	double f = fmaf(a, b, -t);
	return f - e;
}

Quat::Quat(double initX, double initY, double initZ, double initW)
	:X(initX), Y(initY), Z(initZ), W(initW)
{
}

Vec3D Quat::GetEulorValues(bool Convert)
{
	Vec3D angles;
	double t0 = (X + Z) * (X - Z);       // x^2-z^2
	double t1 = (W + Y) * (W - Y);       // w^2-y^2
	double xx = 0.5f * (t0 + t1);
	double xy = f32_mma(X, Y, W, Z);
	double xz = f32_mms(W, Y, X, Z);
	double yz = 2 * (f32_mma(Y, Z, W, X));
	double t = xx * xx + xy * xy;
	double ls = .5f - (Y * Y + Z * Z);
	double Yaw = atan2f(X * Y + W * Z, ls);    // yaw
	double Pitch = atan(xz / sqrtf(0.25f - xz * xz));
	double Roll = 0.f;
	if (t != 0.f)
		Roll = atan2(yz, t1 - t0);
	else
		Roll = 2 * atan2(X, W) - sgn(xz) * Yaw;
	angles[0] = Roll;
	angles[1] = Pitch;
	angles[2] = Yaw;
	if (Convert)
	{
		double conversion = 180.f / PI_F;
		angles.Multiply(conversion);
	}
	return angles;
}

void Quat::Display()
{
	std::cout << "W:" << (*this)[3] << ",";
	std::cout << "X:" << (*this)[0] << ",";
	std::cout << "Y:" << (*this)[1] << ",";
	std::cout << "Z:" << (*this)[2] << "\n";
}

std::string CoatlPhysicsEngine::Quat::GetStr()
{
	std::string str = "[";
	str += " " + std::to_string((*this)[3]);
	for(int ii = 0; ii < 3; ii++)
		str += " " + std::to_string((*this)[ii]);
	return str + " ]\n";
}

void CoatlPhysicsEngine::Quat::SetZeroDegree()
{
	W = 1.0;
	X = Y = Z = 0.0;
}

