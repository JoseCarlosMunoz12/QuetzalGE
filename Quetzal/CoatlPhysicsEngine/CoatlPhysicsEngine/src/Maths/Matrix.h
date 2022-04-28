#pragma once
#include "../define.h"

#include "Vectors.h"
#include <vector>
#include <iostream>
#include <cmath>

namespace CoatlPhysicsEngine {
	/// Matrix functions and class
	class COATL_API MatrixXYD
	{
	private:
		glm::vec3 Pos;
		std::vector<VecXD> Vec;
		void SwapRows(int iRow, int rRow);
		void DevideRow(int Row, double Val);
		void AddRows(int cRow, int bRow, double Factor);
	public:
		int NumRows();
		int NumCols();
		void DisplayMatrix();
		void Transpose();
		void Inverse();
		void Identity();
		void InsertMatrix(int RowID, int ColID, MatrixXYD M);
		MatrixXYD GetIdentity();
		MatrixXYD GetInverse();
		MatrixXYD GetTranspose();
		MatrixXYD GetPsudeoInverse();
		MatrixXYD GetDampedLeastSquares(double Lambda);
		std::string GetStr();
		void MultiplScalar(double Value);
		MatrixXYD(int Row, int Col, double InitVal = 0.f);
		MatrixXYD Concatinate(MatrixXYD A);
		VecXD& operator[] (int ID)
		{
			return Vec[ID];
		}
		MatrixXYD operator* (MatrixXYD L)
		{
			int Rows = (*this).NumCols();
			int Cols = L.NumRows();
			MatrixXYD A(0, 0);
			if (Cols != Rows)
				return A;
			int NewRows = this->NumRows();
			int NewCols = L.NumCols();
			A = MatrixXYD(NewRows, NewCols);
			for (int ii = 0; ii < NewRows; ii++)
				for (int jj = 0; jj < NewCols; jj++)
				{
					double Val = 0.f;
					for (int kk = 0; kk < Rows; kk++)
						Val += (*this)[ii][kk] * L[kk][jj];
					A[ii][jj] = Val;
				}
			return A;
		}
		MatrixXYD operator* (VecXD L)
		{
			int Rows = (*this).NumCols();
			MatrixXYD A(0, 0);
			if (L.Size() != Rows)
				return A;
			int NewRows = this->NumRows();
			A = MatrixXYD(NewRows, 1);
			for (int ii = 0; ii < NewRows; ii++)
			{
				double Val = 0.f;
				for (int kk = 0; kk < Rows; kk++)
					Val += (*this)[ii][kk] * L[kk];
				A[ii][0] = Val;
			}
			return A;
		}
		MatrixXYD operator- (MatrixXYD L)
		{

			int Rows = (*this).NumRows();
			int Cols = (*this).NumCols();
			MatrixXYD A(0, 0);
			if (L.NumRows() != Rows)
				return A;
			if (L.NumRows() != Rows)
				return A;
			A = MatrixXYD(Rows, Cols);
			for (int ii = 0; ii < Rows; ii++)
				for (int jj = 0; jj < Cols; jj++)
					A[ii][jj] = (*this)[ii][jj] - L[ii][jj];
			return A;
		}
		MatrixXYD operator+ (MatrixXYD L)
		{

			int Rows = (*this).NumRows();
			int Cols = (*this).NumCols();
			MatrixXYD A(0, 0);
			if (L.NumRows() != Rows)
				return A;
			if (L.NumRows() != Rows)
				return A;
			A = MatrixXYD(Rows, Cols);
			for (int ii = 0; ii < Rows; ii++)
				for (int jj = 0; jj < Cols; jj++)
					A[ii][jj] = (*this)[ii][jj] + L[ii][jj];
			return A;
		}
		VecXD operator^(VecXD L)
		{
			int Cols = L.Size();
			try
			{
				int Colmns = (*this).NumCols();
				int Cols = L.Size();
				if (Cols != Colmns)
					throw std::runtime_error("Vector doesn't match!!!");
				int NewRows = this->NumRows();
				VecXD Vec(NewRows);
				for (int ii = 0; ii < NewRows; ii++)
				{
					double val = 0.f;
					for (int jj = 0; jj < Cols; jj++)
					{
						val += (*this)[ii][jj] * L[jj];
					}
					Vec[ii] = val;
				}
				return Vec;
			}
			catch (std::runtime_error e)
			{
				return VecXD(Cols, 0);
			}
		}
	};
	class COATL_API Matrix4x4 : public MatrixXYD
	{
	private:
		Quat GetRotation(Vec3D Scale);
	public:
		Matrix4x4();
		Matrix4x4(Quat q);
		void DecomsposeMatrix(Vec3D& Scale, Vec3D& Position, Quat& Rot);
		void DisplayMatrix();
		void Clear(bool full = false);
		Vec3D GetPosition();
		Vec3D GetScale();
		Quat GetRotation();
		Matrix4x4 operator* (Matrix4x4 L)
		{
			int NewRows = this->NumRows();
			int NewCols = L.NumCols();
			Matrix4x4 A;
			for (int ii = 0; ii < 4; ii++)
				for (int jj = 0; jj < 4; jj++)
				{
					double Val = 0.f;
					for (int kk = 0; kk < 4; kk++)
						Val += (*this)[ii][kk] * L[kk][jj];
					A[ii][jj] = Val;
				}
			return A;
		}
		Vec4D operator* (Vec4D L)
		{
			Vec4D A;
			for (int ii = 0; ii < 4; ii++){
				double Val = 0.f;
				for (int jj = 0; jj < 4; jj++)
					Val += (*this)[ii][jj] * L[jj];
				A[ii] = Val;
			}
			return A;
		}
	};
	class COATL_API Matrix3x3 : public MatrixXYD
	{
	private:
		Quat GetRotation(Vec3D Scale);
	public:
		Matrix3x3();
		Matrix3x3(Quat q);
		void DecomsposeMatrix(Vec3D& Scale, Vec3D& Position, Quat& Rot);
		void DisplayMatrix();
		void Clear();
		Vec3D GetPosition();
		Vec3D GetScale();
		Quat GetRotation();
		Matrix3x3 operator* (Matrix3x3 L)
		{
			Matrix3x3 A;
			for (int ii = 0; ii < 3; ii++)
				for (int jj = 0; jj < 3; jj++)
				{
					double Val = 0.f;
					for (int kk = 0; kk < 3; kk++)
						Val += (*this)[ii][kk] * L[kk][jj];
					A[ii][jj] = Val;
				}
			return A;
		}
		Vec3D operator* (Vec3D L)
		{
			Vec3D A;
			for (int ii = 0; ii < 3; ii++)
				for (int jj = 0; jj < 3; jj++)
				{
					double Val = 0.f;
						Val += (*this)[ii][jj] * L[jj];
					A[ii] = Val;
				}
			return A;
		}
		Matrix3x3 operator* (double L)
		{

			Matrix3x3 A;
			for (int ii = 0; ii < 3; ii++)
				for (int jj = 0; jj < 3; jj++)
					A[ii][jj] = (*this)[ii][jj] * L;
			return A;
		}
	};
	class COATL_API Matrix4x3 : public MatrixXYD
	{
	public:
		Matrix4x3(Quat initQuat);
		Quat operator* (Vec3D R)
		{
			Quat ans;

			for (int ii = 0; ii < 4; ii++)
			{
				double t = 0.0;
				for (int jj = 0; ii < 3; jj++)
					t += ((*this)[ii][jj] * R[jj]);
				ans.SetValue(t, ii);
			}
			return ans;
		}
	};
}