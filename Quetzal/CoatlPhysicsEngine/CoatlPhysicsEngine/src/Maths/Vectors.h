#pragma once
#include "../define.h"
#include <vector>
#include <iostream>
#include <cmath>
const double  PI_F = 3.14159265358979f;
namespace CoatlPhysicsEngine {
	class COATL_API VecXD
	{
	private:
		std::vector<double> Vec;
	public:
		VecXD(int Size, double InitVal = 0.f);
		int Size();
		double& operator[] (int loc)
		{
			return Vec[loc];
		}
		double length();
		void Normalize();
		void Multiply(double f);
		std::string GetStr();
		double operator* (VecXD RV)
		{
			int vSize = Size();
			if (vSize != RV.Size())
				throw;
			double val = 0.f;
			for (int ii = 0; ii < vSize; ii++)
				val += (*this)[ii] * RV[ii];
			return val;
		}
		VecXD operator- (VecXD RV)
		{
			VecXD Res(Size());
			for (int ii = 0; ii < Size(); ii++)
				Res[ii] = (*this)[ii] - RV[ii];
			return Res;
		}
		VecXD operator+ (VecXD RV)
		{
			VecXD Res(Size());
			for (int ii = 0; ii < Size(); ii++)
				Res[ii] = (*this)[ii] + RV[ii];
			return Res;
		}
		bool operator == (VecXD RV)
		{
			for (int ii = 0; ii < Size(); ii++)
				if ((*this)[ii] != RV[ii])
					return false;
			return true;
		}
		bool operator != (VecXD RV)
		{
			for (int ii = 0; ii < Size(); ii++)
				if ((*this)[ii] == RV[ii])
					return false;
			return true;
		}
	};
	class COATL_API Vec3D : public VecXD
	{
	public:
		Vec3D();
		Vec3D(double init);
		Vec3D(double x, double y, double z);
		void Display();
		Vec3D SetNormalize();
		Vec3D operator^(Vec3D A)
		{
			Vec3D X;
			X[0] = (*this)[1] * A[2] - (*this)[2] * A[1];
			X[1] = (*this)[2] * A[0] - (*this)[0] * A[2];
			X[2] = (*this)[0] * A[1] - (*this)[1] * A[0];
			return X;
		}
		Vec3D operator- (Vec3D RV)
		{
			Vec3D Res(Size());
			for (int ii = 0; ii < Size(); ii++)
				Res[ii] = (*this)[ii] - RV[ii];
			return Res;
		}
		Vec3D operator+ (Vec3D RV)
		{
			Vec3D Res(Size());
			for (int ii = 0; ii < Size(); ii++)
				Res[ii] = (*this)[ii] + RV[ii];
			return Res;
		}
	};
	class COATL_API Vec4D : public VecXD
	{
	public:
		Vec4D();
		Vec4D(double init);
		Vec4D(Vec3D initVec, double init);
		Vec4D(double w, double x, double y, double z);
		Vec3D GetVec3();
		void Display();
		Vec4D operator- (Vec4D RV)
		{
			Vec4D Res(Size());
			for (int ii = 0; ii < Size(); ii++)
				Res[ii] = (*this)[ii] - RV[ii];
			return Res;
		}
		Vec4D operator+ (Vec4D RV)
		{
			Vec4D Res(Size());
			for (int ii = 0; ii < Size(); ii++)
				Res[ii] = (*this)[ii] + RV[ii];
			return Res;
		}
	};
	class COATL_API Quat
	{
	private:
		double sgn(double x);
		// ab+cd
		double f32_mma(double a, double b, double c, double d);
		// ab-cd
		double f32_mms(double a, double b, double c, double d);
	public:
		double X;
		double Y;
		double Z;
		double W;
		Quat(double initX = 0.f, double initY = 0.f, double initZ = 0.f,
			double initW = 0.f);
		Vec3D GetEulorValues(bool Convert = true);
		void Display();
		std::string GetStr();
		void SetZeroDegree();
		void Multiply(double d);
		double GetValue(int ii);
		void SetValue(double n, int ii);
		double& operator[] (int loc)
		{
			switch (loc)
			{
			case 0:
				return X;
			case 1:
				return Y;
			case 2:
				return Z;
			}
			return W;
		}
	};
}