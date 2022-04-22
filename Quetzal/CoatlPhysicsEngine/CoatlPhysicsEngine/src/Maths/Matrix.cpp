#include "Matrix.h"
using namespace CoatlPhysicsEngine;

///
///MatrixXxYD
///

void MatrixXYD::SwapRows(int iRow, int rRow)
{
	int Cols = this->NumCols();
	for (int ii = 0; ii < Cols; ii++)
		std::swap((*this)[iRow][ii], (*this)[rRow][ii]);
}

void MatrixXYD::DevideRow(int Row, double Val)
{
	int Col = NumCols();
	for (int ii = 0; ii < Col; ii++)
		(*this)[Row][ii] /= Val;
}

void MatrixXYD::AddRows(int cRow, int bRow, double Factor)
{
	int Col = NumCols();
	for (int ii = 0; ii < Col; ii++)
		(*this)[cRow][ii] += Factor * (*this)[bRow][ii];
}

int MatrixXYD::NumRows()
{
	return Vec.size();
}

int MatrixXYD::NumCols()
{
	return Vec[0].Size();
}

void MatrixXYD::DisplayMatrix()
{
	std::cout << "\n";
	int Rows = NumRows();
	int Cols = NumCols();
	for (int ii = 0; ii < Rows; ii++)
	{
		for (int kk = 0; kk < Cols; kk++)
			std::cout << (*this)[ii][kk] << " ";
		std::cout << "\n";
	}

}

void MatrixXYD::Transpose()
{
	int Rows = this->NumCols();
	int Cols = this->NumRows();
	MatrixXYD A(Rows, Cols);
	for (int ii = 0; ii < Rows; ii++)
		for (int jj = 0; jj < Cols; jj++)
			A[ii][jj] = (*this)[jj][ii];
	(*this) = A;
}

void MatrixXYD::Inverse()
{
	int lead = 0;
	int MaxRows = NumRows();
	int MaxCols = NumCols();
	MatrixXYD I = (*this).GetIdentity();
	for (int row = 0; row < MaxRows; row++)
	{
		if (lead > MaxCols)
		{
			(*this) = I;
			return;
		}
		int i = row;
		while ((*this)[i][lead] == 0)
		{
			i++;
			if (i >= MaxRows)
			{
				i = row;
				lead++;
				if (lead > MaxCols)
				{
					(*this) = I;
					return;
				}
			}
		}
		SwapRows(i, row);
		I.SwapRows(i, row);
		double Curdouble = (*this)[row][lead];
		DevideRow(row, Curdouble);
		I.DevideRow(row, Curdouble);
		for (i = 0; i < MaxRows; i++)
		{
			double element = -(*this)[i][lead];
			if (element == 0)
				continue;
			if (i != row)
			{
				AddRows(i, row, element);
				I.AddRows(i, row, element);
			}
		}
	}
	(*this) = I;
}

void MatrixXYD::Identity()
{
	int Rows = NumRows();
	int Col = NumCols();
	if (Rows != Col)
		return;
	for (int ii = 0; ii < Rows; ii++)
		for (int jj = 0; jj < Rows; jj++)
			if (ii == jj)
				(*this)[ii][jj] = 1.f;
			else
				(*this)[ii][jj] = 0.f;
}

void MatrixXYD::InsertMatrix(int RowID, int ColID, MatrixXYD M)
{
	int numRows = M.NumRows();
	int numCols = M.NumCols();
	if ((RowID + numCols) > this->NumRows())
		return;
	if ((ColID + numCols) > this->NumCols())
		return;
	for (int ii = 0; ii < numRows; ii++)
		for (int jj = 0; jj < numCols; jj++)
			(*this)[RowID + ii][ColID + jj] = M[ii][jj];
}

MatrixXYD MatrixXYD::GetIdentity()
{
	MatrixXYD I = (*this);
	I.Identity();
	return I;
}

MatrixXYD MatrixXYD::GetInverse()
{
	MatrixXYD I = (*this);
	I.Inverse();
	return I;
}

MatrixXYD MatrixXYD::GetTranspose()
{
	MatrixXYD T = (*this);
	T.Transpose();
	return T;
}

MatrixXYD MatrixXYD::GetPsudeoInverse()
{
	MatrixXYD T = this->GetTranspose();
	MatrixXYD TO = T * (*this);
	TO.Inverse();
	return TO * T;
}

MatrixXYD MatrixXYD::GetDampedLeastSquares(double Lambda)
{
	MatrixXYD T = this->GetTranspose();
	MatrixXYD JJT = (*this) * T;
	int Rows = JJT.NumRows();
	int Cols = JJT.NumCols();
	MatrixXYD I(Rows, Cols);
	I.Identity();
	Lambda = Lambda * Lambda;
	I.MultiplScalar(Lambda);
	MatrixXYD Inv = JJT + I;
	Inv.Inverse();
	return T * Inv;
}

std::string MatrixXYD::GetStr()
{
	std::string str = "";

	for (int ii = 0; ii < this->NumRows(); ii++)
	{
		str += "|";
		for (int jj = 0; jj < this->NumCols(); jj++)
			str += " " + std::to_string((*this)[ii][jj]);
		str += " |\n";
	}
	return str;
}

void MatrixXYD::MultiplScalar(double Value)
{

	for (int ii = 0; ii < this->NumRows(); ii++)
		for (int jj = 0; jj < this->NumCols(); jj++)
			(*this)[ii][jj] = Value * (*this)[ii][jj];
}

MatrixXYD::MatrixXYD(int Row, int Col, double InitVal)
{
	for (int ii = 0; ii < Row; ii++)
		Vec.push_back(VecXD(Col, InitVal));
}

MatrixXYD MatrixXYD::Concatinate(MatrixXYD A)
{
	int NewCols = NumCols() + A.NumCols();
	int NewRows = NumRows();
	if (NewRows < A.NumRows())
		NewRows = A.NumRows();
	MatrixXYD Mat(NewRows, NewCols);
	for (int ii = 0; ii < NumCols(); ii++)
		for (int jj = 0; jj < NumRows(); jj++)
			Mat[jj][ii] = (*this)[jj][ii];
	int ColCount = 0;
	for (int ii = NumCols(); ii < NewCols; ii++)
	{
		for (int jj = 0; jj < A.NumRows(); jj++)
			Mat[jj][ii] = A[jj][ColCount];
		ColCount++;
	}
	return Mat;
}

///
///Matrix4x4
///

Quat Matrix4x4::GetRotation(Vec3D Scale)
{
	Matrix4x4 T = (*this);
	//Get Transform Columns
	for (int ii = 0; ii < 3; ii++)
		for (int jj = 0; jj < 3; jj++)
			T[jj][ii] = T[jj][ii] / Scale[ii];
	//Get Rotation
	Quat Rot;
	Rot.W = sqrt(std::max(0.0, 1.0 + T[0][0] + T[1][1] + T[2][2])) / 2.0;
	Rot.X = sqrt(std::max(0.0, 1.0 + T[0][0] - T[1][1] - T[2][2])) / 2.0;
	Rot.Y = sqrt(std::max(0.0, 1.0 - T[0][0] + T[1][1] - T[2][2])) / 2.0;
	Rot.Z = sqrt(std::max(0.0, 1.0 - T[0][0] - T[1][1] + T[2][2])) / 2.0;
	Rot.X = std::copysign(Rot.X, T[2][1] - T[1][2]);
	Rot.Y = std::copysign(Rot.Y, T[0][2] - T[2][0]);
	Rot.Z = std::copysign(Rot.Z, T[1][0] - T[0][1]);
	return Rot;
}

Matrix4x4::Matrix4x4()
	:MatrixXYD(4, 4)
{
	this->Identity();
}

Matrix4x4::Matrix4x4(Quat q)
	: MatrixXYD(4, 4)
{
	double sqw = q.W * q.W;
	double sqx = q.X * q.X;
	double sqy = q.Y * q.Y;
	double sqz = q.Z * q.Z;
	// to normalize Quat if not already
	double invs = 1.f / (sqw + sqx + sqy + sqz);
	(*this)[0][0] = (sqx - sqy - sqz + sqw) * invs;
	(*this)[1][1] = (-sqx + sqy - sqz + sqw) * invs;
	(*this)[2][2] = (-sqx - sqy + sqz + sqw) * invs;

	double temp1 = q.X * q.Y;
	double temp2 = q.Z * q.W;
	(*this)[1][0] = 2.f * (temp1 + temp2) * invs;
	(*this)[0][1] = 2.f * (temp1 - temp2) * invs;

	temp1 = q.X * q.Z;
	temp2 = q.Y * q.W;
	(*this)[2][0] = 2.f * (temp1 - temp2) * invs;
	(*this)[0][2] = 2.f * (temp1 + temp2) * invs;

	temp1 = q.Y * q.Z;
	temp2 = q.X * q.W;
	(*this)[2][1] = 2.f * (temp1 + temp2) * invs;
	(*this)[1][2] = 2.f * (temp1 - temp2) * invs;

	(*this)[3][3] = 1.f;
}

void Matrix4x4::DecomsposeMatrix(Vec3D& Scale, Vec3D& Position, Quat& Rot)
{
	//Get Translation
	Position = this->GetPosition();
	//Get Scale
	Scale = this->GetScale();
	//Get Rotation
	Rot = this->GetRotation(Scale);
}

void Matrix4x4::DisplayMatrix()
{
	for (int ii = 0; ii < 4; ii++)
	{
		for (int jj = 0; jj < 4; jj++)
		{
			std::cout << (*this)[ii][jj] << " ";
		}
		std::cout << " \n";
	}
}

void Matrix4x4::Clear(bool full)
{
	(*this)[0][0] = 0.f;
	(*this)[1][1] = 0.f;
	(*this)[2][2] = 0.f;
	if (full)
		(*this)[3][3] = 0.f;
}

Vec3D Matrix4x4::GetPosition()
{
	Vec3D Pos;
	Pos[0] = (*this)[0][3];
	Pos[1] = (*this)[1][3];
	Pos[2] = (*this)[2][3];
	return Pos;
}

Vec3D Matrix4x4::GetScale()
{
	Vec3D Scale;
	Vec3D Row[3];
	for (int ii = 0; ii < 3; ii++)
		for (int jj = 0; jj < 3; jj++)
			Row[ii][jj] = (*this)[ii][jj];
	for (int ii = 0; ii < 3; ii++)
		Scale[ii] = Row[ii].length();
	return Scale;
}

Quat Matrix4x4::GetRotation()
{
	Vec3D Scale = this->GetScale();
	Matrix4x4 T = (*this);
	//Get Transform Columns
	for (int ii = 0; ii < 3; ii++)
		for (int jj = 0; jj < 3; jj++)
			T[jj][ii] = T[jj][ii] / Scale[ii];
	//Get Rotation
	Quat Rot;
	Rot.W = sqrt(std::max(0.0, 1.0 + T[0][0] + T[1][1] + T[2][2])) / 2.0;
	Rot.X = sqrt(std::max(0.0, 1.0 + T[0][0] - T[1][1] - T[2][2])) / 2.0;
	Rot.Y = sqrt(std::max(0.0, 1.0 - T[0][0] + T[1][1] - T[2][2])) / 2.0;
	Rot.Z = sqrt(std::max(0.0, 1.0 - T[0][0] - T[1][1] + T[2][2])) / 2.0;
	Rot.X = std::copysign(Rot.X, T[2][1] - T[1][2]);
	Rot.Y = std::copysign(Rot.Y, T[0][2] - T[2][0]);
	Rot.Z = std::copysign(Rot.Z, T[1][0] - T[0][1]);
	return Rot;
}

///
///Matrix3x3 
///

Quat Matrix3x3::GetRotation(Vec3D Scale)
{
	Matrix3x3 T = (*this);
	//Get Transform Columns
	for (int ii = 0; ii < 3; ii++)
		for (int jj = 0; jj < 3; jj++)
			T[jj][ii] = T[jj][ii] / Scale[ii];
	//Get Rotation
	Quat Rot;
	Rot.W = sqrt(std::max(0.0, 1.0 + T[0][0] + T[1][1] + T[2][2])) / 2.0;
	Rot.X = sqrt(std::max(0.0, 1.0 + T[0][0] - T[1][1] - T[2][2])) / 2.0;
	Rot.Y = sqrt(std::max(0.0, 1.0 - T[0][0] + T[1][1] - T[2][2])) / 2.0;
	Rot.Z = sqrt(std::max(0.0, 1.0 - T[0][0] - T[1][1] + T[2][2])) / 2.0;
	Rot.X = std::copysign(Rot.X, T[2][1] - T[1][2]);
	Rot.Y = std::copysign(Rot.Y, T[0][2] - T[2][0]);
	Rot.Z = std::copysign(Rot.Z, T[1][0] - T[0][1]);
	return Rot;
}

Matrix3x3::Matrix3x3()
	:MatrixXYD(3, 3)
{
	this->Identity();
}

Matrix3x3::Matrix3x3(Quat q)
	: MatrixXYD(3, 3)
{
	double sqw = q.W * q.W;
	double sqx = q.X * q.X;
	double sqy = q.Y * q.Y;
	double sqz = q.Z * q.Z;
	// to normalize Quat if not already
	double invs = 1.f / (sqw + sqx + sqy + sqz);
	(*this)[0][0] = (sqx - sqy - sqz + sqw) * invs;
	(*this)[1][1] = (-sqx + sqy - sqz + sqw) * invs;
	(*this)[2][2] = (-sqx - sqy + sqz + sqw) * invs;

	double temp1 = q.X * q.Y;
	double temp2 = q.Z * q.W;
	(*this)[1][0] = 2.f * (temp1 + temp2) * invs;
	(*this)[0][1] = 2.f * (temp1 - temp2) * invs;

	temp1 = q.X * q.Z;
	temp2 = q.Y * q.W;
	(*this)[2][0] = 2.f * (temp1 - temp2) * invs;
	(*this)[0][2] = 2.f * (temp1 + temp2) * invs;

	temp1 = q.Y * q.Z;
	temp2 = q.X * q.W;
	(*this)[2][1] = 2.f * (temp1 + temp2) * invs;
	(*this)[1][2] = 2.f * (temp1 - temp2) * invs;
}

void Matrix3x3::DecomsposeMatrix(Vec3D& Scale, Vec3D& Position, Quat& Rot)
{
	//Get Translation
	Position = this->GetPosition();
	//Get Scale
	Scale = this->GetScale();
	//Get Rotation
	Rot = this->GetRotation(Scale);
}

void Matrix3x3::DisplayMatrix()
{
	for (int ii = 0; ii < 3; ii++)
	{
		for (int jj = 0; jj < 3; jj++)
		{
			std::cout << (*this)[ii][jj] << " ";
		}
		std::cout << " \n";
	}
}

void Matrix3x3::Clear()
{
	(*this)[0][0] = 0.f;
	(*this)[1][1] = 0.f;
	(*this)[2][2] = 0.f;
}

Vec3D Matrix3x3::GetPosition()
{
	Vec3D Pos;
	Pos[0] = (*this)[0][3];
	Pos[1] = (*this)[1][3];
	Pos[2] = (*this)[2][3];
	return Pos;
}

Vec3D Matrix3x3::GetScale()
{
	Vec3D Scale;
	Vec3D Row[3];
	for (int ii = 0; ii < 3; ii++)
		for (int jj = 0; jj < 3; jj++)
			Row[ii][jj] = (*this)[ii][jj];
	for (int ii = 0; ii < 3; ii++)
		Scale[ii] = Row[ii].length();
	return Scale;
}

Quat Matrix3x3::GetRotation()
{
	Vec3D Scale = this->GetScale();
	Matrix3x3 T = (*this);
	//Get Transform Columns
	for (int ii = 0; ii < 3; ii++)
		for (int jj = 0; jj < 3; jj++)
			T[jj][ii] = T[jj][ii] / Scale[ii];
	//Get Rotation
	Quat Rot;
	Rot.W = sqrt(std::max(0.0, 1.0 + T[0][0] + T[1][1] + T[2][2])) / 2.0;
	Rot.X = sqrt(std::max(0.0, 1.0 + T[0][0] - T[1][1] - T[2][2])) / 2.0;
	Rot.Y = sqrt(std::max(0.0, 1.0 - T[0][0] + T[1][1] - T[2][2])) / 2.0;
	Rot.Z = sqrt(std::max(0.0, 1.0 - T[0][0] - T[1][1] + T[2][2])) / 2.0;
	Rot.X = std::copysign(Rot.X, T[2][1] - T[1][2]);
	Rot.Y = std::copysign(Rot.Y, T[0][2] - T[2][0]);
	Rot.Z = std::copysign(Rot.Z, T[1][0] - T[0][1]);
	return Rot;
}

Matrix4x3::Matrix4x3(Quat initQuat)
	:MatrixXYD(4,3)
{
	(*this)[0][0] = -initQuat.X; (*this)[0][1] = -initQuat.Y; (*this)[0][2] = -initQuat.Z;
	(*this)[0][0] =  initQuat.W; (*this)[0][1] =  initQuat.Z; (*this)[0][2] = -initQuat.Y;
	(*this)[0][0] = -initQuat.Z; (*this)[0][1] =  initQuat.W; (*this)[0][2] =  initQuat.X;
	(*this)[0][0] =  initQuat.Y; (*this)[0][1] = -initQuat.X; (*this)[0][2] =  initQuat.W;
}

