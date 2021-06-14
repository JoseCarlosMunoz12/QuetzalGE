#pragma once
#include <vector>
#include <map>
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <iostream>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../Render_Items/Vertex.h"

class Primitive

{
private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

public:
	Primitive()
	{

	}
	virtual ~Primitive()
	{

	}
	void set(const Vertex* vertices, const unsigned nrofVertices,
		const GLuint* indices,const unsigned nrOfIndices)
	{
		for (int i = 0; i < nrofVertices; i++)
		{
			this->vertices.push_back(vertices[i]);
		}
		for (int i = 0; i < nrOfIndices; i++)
		{
			this->indices.push_back(indices[i]);
		}
	}
	void set(std::vector<Vertex> vertexFound, std::vector<GLuint> indicesFound)
	{
		this->vertices = vertexFound;
		this->indices = indicesFound;
	}
	inline Vertex* getVertices() { return this->vertices.data();}
	inline GLuint* getIndices() { return this->indices.data();}

	inline const unsigned getNrOfVertices() { return this->vertices.size(); }
	inline const unsigned getNrOfIndices() { return this->indices.size(); }

};

class Quad_M : public Primitive
{
public:
	Quad_M()
		:Primitive()
	{
		Vertex vertices[] =
		{
			//Position                    //TexCoords			 //Normals
			glm::vec3(-1.f, 1.f, 0.f), glm::vec2(0.0f,1.0f),  glm::vec3(0.0f,0.0f, 1.0f),
			glm::vec3( 1.f, 1.f, 0.f), glm::vec2(1.0f,1.0f),  glm::vec3(0.0f,0.0f, 1.0f),
			glm::vec3(-1.f,-1.f, 0.f), glm::vec2(0.0f,0.0f),  glm::vec3(0.0f,0.0f, 1.0f),
			glm::vec3( 1.f,-1.f, 0.f), glm::vec2(1.0f,0.0f),  glm::vec3(0.0f,0.0f, 1.0f)
		};
		unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

		GLuint indices[] =
		{
			0,2,1, //Trianlge 1
			1,2,3  //Triangle 2
		};
		unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

		this->set(vertices, nrOfVertices, indices, nrOfIndices);
	}
};

class PlaneTerrain_M: public Primitive
{
public:
	PlaneTerrain_M()
		:Primitive()
	{
		Vertex vertices[] = 
		{
			//Position                     //TexCoords			 //Normals
			glm::vec3(-50.f, 0.f, 50.f),  glm::vec2(0.0f,1.0f),  glm::vec3( 0.0f, 1.0f, 0.0f),
			glm::vec3(-50.f, 0.f,-50.f),  glm::vec2(0.0f,0.0f),  glm::vec3( 0.0f, 1.0f, 0.0f),
			glm::vec3( 50.f, 0.f, 50.f),  glm::vec2(1.0f,1.0f),  glm::vec3( 0.0f, 1.0f, 0.0f),
			glm::vec3( 50.f, 0.f,-50.f),  glm::vec2(1.0f,0.0f),  glm::vec3( 0.0f, 1.0f, 0.0f)
		};
		unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

		GLuint indices[] =
		{
			0,2,1,  //Triangle 1
			2,3,1  //Trianlge 2
		};
		unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

		this->set(vertices, nrOfVertices, indices, nrOfIndices);
	}
};

class Triangle_M : public Primitive
{
public:
	Triangle_M()
		:Primitive()
	{
		Vertex vertices[] =
		{
			//Position                     //TexCoords			 //Normals
			glm::vec3(-0.5f, 0.5f, 0.f),  glm::vec2(0.0f,1.0f),  glm::vec3(0.0f,0.0f, 1.0f),
			glm::vec3(-0.5f,-0.5f, 0.f),  glm::vec2(0.0f,0.0f),  glm::vec3(0.0f,0.0f, 1.0f),
			glm::vec3( 0.5f,-0.5f, 0.f),  glm::vec2(1.0f,0.0f),  glm::vec3(0.0f,0.0f, 1.0f)
		};
		unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

		GLuint indices[] =
		{
			0,1,2, //Trianlge 1
		};
		unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

		this->set(vertices, nrOfVertices, indices, nrOfIndices);
	}
	Triangle_M(std::vector<glm::vec3> Points)
	{
		std::vector<Vertex> AllVertex;
		glm::vec3 Norm = glm::cross((Points[0]-Points[1]), (Points[0] - Points[2]));
		glm::vec2 TexCo[3] = {glm::vec2(1.0f, 0.0f),
							  glm::vec2(0.0f, 0.0f),
							  glm::vec2(0.0f, 1.0f)};
		int Count = 0;
		for (auto& jj : Points)
		{
			Vertex Temp{};
			Temp.position = jj;
			Temp.normal = Norm;
			Temp.texcoord = TexCo[Count];
			Count++;
			AllVertex.push_back(Temp);
		}
		std::vector<GLuint> Index = {2,1,0};
		this->set(AllVertex, Index);
	}
};

class Pyramid_M: public Primitive
{
public:
	Pyramid_M()
		: Primitive()
	{
		Vertex vertices[] =
		{
			//Position							//Texcoords					//Normals
			//Triangle front
			glm::vec3(0.f, 0.5f, 0.f),			glm::vec2(0.5f, 1.f),		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(-0.5f, -0.5f, 0.5f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f, -0.5f, 0.5f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),

			//Triangle left
			glm::vec3(0.f, 0.5f, 0.f),			glm::vec2(0.5f, 1.f),		glm::vec3(-1.f, 0.f, 0.f),
			glm::vec3(-0.5f, -0.5f, -0.5f),		glm::vec2(0.f, 0.f),		glm::vec3(-1.f, 0.f, 0.f),
			glm::vec3(-0.5f, -0.5f, 0.5f),		glm::vec2(1.f, 0.f),		glm::vec3(-1.f, 0.f, 0.f),

			//Triangle back
			glm::vec3(0.f, 0.5f, 0.f),			glm::vec2(0.5f, 1.f),		glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(0.5f, -0.5f, -0.5f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(-0.5f, -0.5f, -0.5f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, -1.f),

			//Triangles right
			glm::vec3(0.f, 0.5f, 0.f),			glm::vec2(0.5f, 1.f),		glm::vec3(1.f, 0.f, 0.f),
			glm::vec3(0.5f, -0.5f, 0.5f),		glm::vec2(0.f, 0.f),		glm::vec3(1.f, 0.f, 0.f),
			glm::vec3(0.5f, -0.5f, -0.5f),		glm::vec2(1.f, 0.f),		glm::vec3(1.f, 0.f, 0.f),
		};
		unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

		this->set(vertices, nrOfVertices, nullptr, 0);
	}
};

class Cube_M : public Primitive
{
public:
	Cube_M()
		:Primitive()
	{
		std::vector<Vertex> VertexOfCube;
		std::vector<GLuint> IndecesOfCube;
		glm::vec3 Normals[] =
		{
			glm::vec3(1.f,0.f,0.f), glm::vec3(0.f,1.f,0.f), glm::vec3(-1.f,0.f,0.f), glm::vec3(0.f,-1.f,0.f),
			glm::vec3(0.f,0.f,1.f), glm::vec3(0.f,0.f,-1.f)
		};
		glm::vec2 TexCoords[] =
		{
			glm::vec2(0.f,0.f),glm::vec2(1.f,0.f),
			glm::vec2(0.f,1.f),glm::vec2(1.f,1.f)
		};
		glm::vec3 Positions[] =
		{
			//Top Plane 
			glm::vec3(0.5f,-0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f),
			glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-0.5f,-0.5f, 0.5f),
			//Bottom Plane
			glm::vec3(0.5f,-0.5f,-0.5f), glm::vec3(0.5f, 0.5f,-0.5f),
			glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec3(-0.5f,-0.5f,-0.5f)
		};
		int Index[] = {0,4,1,5};

		for (int ii = 0; ii < 4; ii++)
		{
			VertexOfCube.push_back({ Positions[Index[0]],TexCoords[2],Normals[ii] });
			VertexOfCube.push_back({ Positions[Index[1]],TexCoords[0],Normals[ii] });
			VertexOfCube.push_back({ Positions[Index[2]],TexCoords[3],Normals[ii] });
			VertexOfCube.push_back({ Positions[Index[2]],TexCoords[3],Normals[ii] });
			VertexOfCube.push_back({ Positions[Index[1]],TexCoords[0],Normals[ii] });
			VertexOfCube.push_back({ Positions[Index[3]],TexCoords[1],Normals[ii] });
			Index[0]++;
			Index[1]++;
			Index[2]++;
			Index[3]++;
			if (Index[2] == 4)
			{
				Index[2] = 0;
			}
			if (Index[3] == 8)
			{
				Index[3] = 4;
			}
		}
		int TopIndex[] = {3,0,2,1};
		for (int ii = 4; ii < 6; ii++)
		{

			VertexOfCube.push_back({ Positions[TopIndex[0]],TexCoords[2],Normals[ii] });
			VertexOfCube.push_back({ Positions[TopIndex[1]],TexCoords[0],Normals[ii] });
			VertexOfCube.push_back({ Positions[TopIndex[2]],TexCoords[3],Normals[ii] });
			VertexOfCube.push_back({ Positions[TopIndex[2]],TexCoords[3],Normals[ii] });
			VertexOfCube.push_back({ Positions[TopIndex[1]],TexCoords[0],Normals[ii] });
			VertexOfCube.push_back({ Positions[TopIndex[3]],TexCoords[1],Normals[ii] });
			TopIndex[0] = 6;
			TopIndex[1] = 5;
			TopIndex[2] = 7;
			TopIndex[3] = 4;
		}

		int Count = 0;
		for (auto& jj : VertexOfCube)
		{
			IndecesOfCube.push_back(Count);
			Count++;
		}
		this->set(VertexOfCube, IndecesOfCube);
	}

	Cube_M(int Dimension, float DimensionSize)
		:Primitive()
	{
		std::vector<Vertex> VertexOfCube;
		std::vector<GLuint> IndecesOfCube;
		glm::vec3 Normals[] =
		{
			glm::vec3(0.f,0.f,1.f), glm::vec3(-1.f,0.f,0.f),
			glm::vec3(0.f,0.f,-1.f),glm::vec3(1.f,0.f,0.f),
		};
		int EndIndex[] = {0	, Dimension , 2*Dimension ,
							3 *  Dimension , 4 * Dimension};
		int SizeIndex[] = { Dimension, Dimension, Dimension, Dimension };
		int DimensionFaces[] = { 0	, Dimension * Dimension, (2*Dimension ) * Dimension ,
							(3 * Dimension ) * Dimension};
		for (int kk = 0; kk < 4; kk++)
		{
			for (int ii = 0; ii < Dimension; ii++)
			{
				for (int jj = 0; jj < Dimension; jj++)
				{
					glm::vec2 TexCord = CalcTexcoords(Dimension - 1, Dimension - 1, Dimension - 1, kk, jj, ii);
					glm::vec3 Positions = CalculatePosition(Dimension - 1, Dimension - 1, Dimension - 1,
															DimensionSize, DimensionSize,DimensionSize, kk, jj,ii);
					Vertex TempVertex = { Positions,TexCord,Normals[kk] };
					VertexOfCube.push_back(TempVertex);
				}
			}
		}
			//Need to Create ALgorithm to make the Indicies of the Box
			//For each of the four size
		for (int kk = 0; kk < 4; kk++)
		{
			for (int ii = 0; ii < Dimension-1;ii++)
			{
				for (int jj = 0; jj < Dimension-1; jj++)
				{
					GLuint TopRight = (ii * Dimension) + jj + DimensionFaces[kk];
					GLuint TopLeft = TopRight + 1;
					GLuint BottomRight = ((ii + 1) * Dimension) + jj + DimensionFaces[kk];
					GLuint BottomLeft = BottomRight + 1;
					IndecesOfCube.push_back(TopLeft);
					IndecesOfCube.push_back(BottomLeft);
					IndecesOfCube.push_back(TopRight);
					IndecesOfCube.push_back(TopRight);
					IndecesOfCube.push_back(BottomLeft);
					IndecesOfCube.push_back(BottomRight);
				}
			}
		}
		this->set(VertexOfCube, IndecesOfCube);
	}
private:
	glm::vec3 CalculatePosition(int Length, int Height, int width,
								float LengthSize, float HeightSize, float WidthSize,
								int Mode,int IndexX, int IndexY)
	{
		glm::vec3 TempPos = glm::vec3(1.f,1.f,1.f);
		switch (Mode)
		{
		case 0 :
			TempPos.x = float(HeightSize) * float(Height -2 * IndexX)/ float(2*Height);
			TempPos.y = float(WidthSize) * float(width - 2 * IndexY) / float(2 * width);
			TempPos.z = float(LengthSize) /2;
			break;
		case 1:
			TempPos.x = -1 * float(WidthSize) / 2;
			TempPos.y = float(HeightSize) * float(Height - 2 * IndexY) / float(2 * Height);
			TempPos.z = float(LengthSize) * float(Length - 2 * IndexX ) / float(2 * Length);
			break;
		case 2:
			TempPos.x = float(HeightSize) * float( 2 * IndexX - Height) / float(2 * Height);
			TempPos.y = -1 * float(WidthSize) * float(2 * IndexY - width) / float(2 * width);
			TempPos.z = -1 * float(LengthSize) / 2;
			break;
		case 3:
			TempPos.x = float(WidthSize) / 2;
			TempPos.y = float(HeightSize) * float(Height - 2 * IndexY) / float(2 * Height);
			TempPos.z = -1 * float(LengthSize) * float(Length - 2 * IndexX) / float(2 * Length);
			break;
		}
		return TempPos;
	}
	glm::vec2 CalcTexcoords(int Width, int Length, int Height, int Mode, int ii, int jj)
	{
		glm::vec2 TempTexCoord = glm::vec2(1.f,1.f);
		switch (Mode)
		{
		case 0:
		case 2:
			TempTexCoord.x = (float)(Height - ii) / ((float)Height);
			TempTexCoord.y = (float)(Width - jj) / ((float)Width);
			break;
		case 1:
		case 3:
			TempTexCoord.x = (float)(Height - ii) / ((float)Height);
			TempTexCoord.y = (float)(Length - jj) / ((float)Length);
			break;
		}
		return TempTexCoord;
	}
};

class Prism_M : public Primitive
{
public:
	Prism_M(float DimXYZ) {

		std::vector<Vertex> VertexOfCube;
		std::vector<GLuint> IndecesOfCube;
		glm::vec3 Normals[] =
		{
			glm::vec3(1.f,0.f,0.f), glm::vec3(0.f,1.f,0.f), glm::vec3(-1.f,0.f,0.f), glm::vec3(0.f,-1.f,0.f),
			glm::vec3(0.f,0.f,1.f), glm::vec3(0.f,0.f,-1.f)
		};
		glm::vec2 TexCoords[] =
		{
			glm::vec2(0.f,0.f),glm::vec2(1.f,0.f),
			glm::vec2(0.f,1.f),glm::vec2(1.f,1.f)
		};
		glm::vec3 Positions[] =
		{
			//Top Plane 
			glm::vec3(DimXYZ,-DimXYZ, DimXYZ), glm::vec3(DimXYZ, DimXYZ, DimXYZ),
			glm::vec3(-DimXYZ, DimXYZ, DimXYZ), glm::vec3(-DimXYZ,-DimXYZ, DimXYZ),
			//Bottom Plane
			glm::vec3(DimXYZ,-DimXYZ,-DimXYZ), glm::vec3(DimXYZ, DimXYZ,-DimXYZ),
			glm::vec3(-DimXYZ, DimXYZ,-DimXYZ), glm::vec3(-DimXYZ,-DimXYZ,-DimXYZ)
		};
		int Index[] = { 0,4,1,5 };

		for (int ii = 0; ii < 4; ii++)
		{
			VertexOfCube.push_back({ Positions[Index[0]],TexCoords[2],Normals[ii] });
			VertexOfCube.push_back({ Positions[Index[1]],TexCoords[0],Normals[ii] });
			VertexOfCube.push_back({ Positions[Index[2]],TexCoords[3],Normals[ii] });
			VertexOfCube.push_back({ Positions[Index[2]],TexCoords[3],Normals[ii] });
			VertexOfCube.push_back({ Positions[Index[1]],TexCoords[0],Normals[ii] });
			VertexOfCube.push_back({ Positions[Index[3]],TexCoords[1],Normals[ii] });
			Index[0]++;
			Index[1]++;
			Index[2]++;
			Index[3]++;
			if (Index[2] == 4)
			{
				Index[2] = 0;
			}
			if (Index[3] == 8)
			{
				Index[3] = 4;
			}
		}
		int TopIndex[] = { 3,0,2,1 };
		for (int ii = 4; ii < 6; ii++)
		{

			VertexOfCube.push_back({ Positions[TopIndex[0]],TexCoords[2],Normals[ii] });
			VertexOfCube.push_back({ Positions[TopIndex[1]],TexCoords[0],Normals[ii] });
			VertexOfCube.push_back({ Positions[TopIndex[2]],TexCoords[3],Normals[ii] });
			VertexOfCube.push_back({ Positions[TopIndex[2]],TexCoords[3],Normals[ii] });
			VertexOfCube.push_back({ Positions[TopIndex[1]],TexCoords[0],Normals[ii] });
			VertexOfCube.push_back({ Positions[TopIndex[3]],TexCoords[1],Normals[ii] });
			TopIndex[0] = 6;
			TopIndex[1] = 5;
			TopIndex[2] = 7;
			TopIndex[3] = 4;
		}

		int Count = 0;
		for (auto& jj : VertexOfCube)
		{
			IndecesOfCube.push_back(Count);
			Count++;
		}
		this->set(VertexOfCube, IndecesOfCube);
	}
	Prism_M(float DimX, float DimYZ) {

		std::vector<Vertex> VertexOfCube;
		std::vector<GLuint> IndecesOfCube;
		glm::vec3 Normals[] =
		{
			glm::vec3(1.f,0.f,0.f), glm::vec3(0.f,1.f,0.f), glm::vec3(-1.f,0.f,0.f), glm::vec3(0.f,-1.f,0.f),
			glm::vec3(0.f,0.f,1.f), glm::vec3(0.f,0.f,-1.f)
		};
		glm::vec2 TexCoords[] =
		{
			glm::vec2(0.f,0.f),glm::vec2(1.f,0.f),
			glm::vec2(0.f,1.f),glm::vec2(1.f,1.f)
		};
		glm::vec3 ColorsUsed = glm::vec3(0.f, 0.f, 1.f);
		glm::vec3 Positions[] =
		{
			//Top Plane 
			glm::vec3(DimX ,-DimYZ , DimYZ ), glm::vec3(DimX , DimYZ , DimYZ ),
			glm::vec3(-DimX , DimYZ , DimYZ ), glm::vec3(-DimX ,-DimYZ , DimYZ ),
			//Bottom Plane
			glm::vec3(DimX ,-DimYZ ,-DimYZ ), glm::vec3(DimX , DimYZ ,-DimYZ ),
			glm::vec3(-DimX , DimYZ ,-DimYZ ), glm::vec3(-DimX ,-DimYZ ,-DimYZ )
		};
		int Index[] = { 0,4,1,5 };

		for (int ii = 0; ii < 4; ii++)
		{
			VertexOfCube.push_back({ Positions[Index[0]],TexCoords[2],Normals[ii] });
			VertexOfCube.push_back({ Positions[Index[1]],TexCoords[0],Normals[ii] });
			VertexOfCube.push_back({ Positions[Index[2]],TexCoords[3],Normals[ii] });
			VertexOfCube.push_back({ Positions[Index[2]],TexCoords[3],Normals[ii] });
			VertexOfCube.push_back({ Positions[Index[1]],TexCoords[0],Normals[ii] });
			VertexOfCube.push_back({ Positions[Index[3]],TexCoords[1],Normals[ii] });
			Index[0]++;
			Index[1]++;
			Index[2]++;
			Index[3]++;
			if (Index[2] == 4)
			{
				Index[2] = 0;
			}
			if (Index[3] == 8)
			{
				Index[3] = 4;
			}
		}
		int TopIndex[] = { 3,0,2,1 };
		for (int ii = 4; ii < 6; ii++)
		{

			VertexOfCube.push_back({ Positions[TopIndex[0]],TexCoords[2],Normals[ii] });
			VertexOfCube.push_back({ Positions[TopIndex[1]],TexCoords[0],Normals[ii] });
			VertexOfCube.push_back({ Positions[TopIndex[2]],TexCoords[3],Normals[ii] });
			VertexOfCube.push_back({ Positions[TopIndex[2]],TexCoords[3],Normals[ii] });
			VertexOfCube.push_back({ Positions[TopIndex[1]],TexCoords[0],Normals[ii] });
			VertexOfCube.push_back({ Positions[TopIndex[3]],TexCoords[1],Normals[ii] });
			TopIndex[0] = 6;
			TopIndex[1] = 5;
			TopIndex[2] = 7;
			TopIndex[3] = 4;
		}

		int Count = 0;
		for (auto& jj : VertexOfCube)
		{
			IndecesOfCube.push_back(Count);
			Count++;
		}
		this->set(VertexOfCube, IndecesOfCube);
	}
	Prism_M(float DimX, float DimY, float DimZ) {

		std::vector<Vertex> VertexOfCube;
		std::vector<GLuint> IndecesOfCube;
		glm::vec3 Normals[] =
		{
			glm::vec3(1.f,0.f,0.f), glm::vec3(0.f,1.f,0.f), glm::vec3(-1.f,0.f,0.f), glm::vec3(0.f,-1.f,0.f),
			glm::vec3(0.f,0.f,1.f), glm::vec3(0.f,0.f,-1.f)
		};
		glm::vec2 TexCoords[] =
		{
			glm::vec2(0.f,0.f),glm::vec2(1.f,0.f),
			glm::vec2(0.f,1.f),glm::vec2(1.f,1.f)
		};
		glm::vec3 ColorsUsed = glm::vec3(0.f, 0.f, 1.f);
		glm::vec3 Positions[] =
		{
			//Top Plane 
			glm::vec3(DimX ,-DimY , DimZ ), glm::vec3(DimX , DimY , DimZ ),
			glm::vec3(-DimX , DimY , DimZ ), glm::vec3(-DimX ,-DimY , DimZ ),
			//Bottom Plane
			glm::vec3(DimX ,-DimY ,-DimZ ), glm::vec3(DimX , DimY ,-DimZ ),
			glm::vec3(-DimX , DimY ,-DimZ ), glm::vec3(-DimX ,-DimY ,-DimZ )
		};
		int Index[] = { 0,4,1,5 };

		for (int ii = 0; ii < 4; ii++)
		{
			VertexOfCube.push_back({ Positions[Index[0]],TexCoords[2],Normals[ii] });
			VertexOfCube.push_back({ Positions[Index[1]],TexCoords[0],Normals[ii] });
			VertexOfCube.push_back({ Positions[Index[2]],TexCoords[3],Normals[ii] });
			VertexOfCube.push_back({ Positions[Index[2]],TexCoords[3],Normals[ii] });
			VertexOfCube.push_back({ Positions[Index[1]],TexCoords[0],Normals[ii] });
			VertexOfCube.push_back({ Positions[Index[3]],TexCoords[1],Normals[ii] });
			Index[0]++;
			Index[1]++;
			Index[2]++;
			Index[3]++;
			if (Index[2] == 4)
			{
				Index[2] = 0;
			}
			if (Index[3] == 8)
			{
				Index[3] = 4;
			}
		}
		int TopIndex[] = { 3,0,2,1 };
		for (int ii = 4; ii < 6; ii++)
		{

			VertexOfCube.push_back({ Positions[TopIndex[0]],TexCoords[2],Normals[ii] });
			VertexOfCube.push_back({ Positions[TopIndex[1]],TexCoords[0],Normals[ii] });
			VertexOfCube.push_back({ Positions[TopIndex[2]],TexCoords[3],Normals[ii] });
			VertexOfCube.push_back({ Positions[TopIndex[2]],TexCoords[3],Normals[ii] });
			VertexOfCube.push_back({ Positions[TopIndex[1]],TexCoords[0],Normals[ii] });
			VertexOfCube.push_back({ Positions[TopIndex[3]],TexCoords[1],Normals[ii] });
			TopIndex[0] = 6;
			TopIndex[1] = 5;
			TopIndex[2] = 7;
			TopIndex[3] = 4;
		}

		int Count = 0;
		for (auto& jj : VertexOfCube)
		{
			IndecesOfCube.push_back(Count);
			Count++;
		}
		this->set(VertexOfCube, IndecesOfCube);
	}
};

class CustomObject_M: public Primitive
{
public:
	CustomObject_M(const char* file)
		:Primitive()
	{

		std::string FileLoc = "";
		//Variables to Get info from the obj file
		this->InitStringZFound();
		std::string temp = "Models/ModelObj/";
		temp += file;
		std::vector<glm::vec3> PositionsFound;
		std::vector<glm::vec2> TexCoordsFound;
		std::vector<glm::vec3> NormalsFound;
		std::vector<std::string> IndexToUse;
		std::ifstream in_file;
		//Vertex and Index Info
		std::vector<Vertex> VertexFound;
		std::vector<GLuint> IndecesFound;
		//Opens Obj File
		in_file.open(temp.c_str());
		//Searches the obj file and get all neccesssary info
		if (in_file.is_open())
		{
			while (std::getline(in_file, temp))
			{
				std::vector<std::string> out;
				this->ReturnStringArray(temp, ' ', out);
				switch (this->StringFound[out[0]])
				{
				case V:
					PositionsFound.push_back(glm::vec3(std::atof(out[1].c_str()), std::atof(out[2].c_str()), std::atof(out[3].c_str())));
					break;
				case VT:
					TexCoordsFound.push_back(glm::vec2(std::atof(out[1].c_str()), std::atof(out[2].c_str())));
					break;
				case VN:
					NormalsFound.push_back(glm::vec3(std::atof(out[1].c_str()), std::atof(out[2].c_str()), std::atof(out[3].c_str())));
					break;
				case F:
					IndexToUse.push_back(out[1]);
					IndexToUse.push_back(out[2]);
					IndexToUse.push_back(out[3]);
					break;
				default:
					break;
				}
			}
		}
		//Sorts all Data and makes the Vertex and Indeces
		for (auto& ii : IndexToUse)
		{
			std::vector<std::string> out;
			this->ReturnStringArray(ii,'/', out);
			VertexFound.push_back({ PositionsFound[std::atof(out[0].c_str())-1],
									TexCoordsFound[std::atof(out[1].c_str()) - 1],
									NormalsFound[std::atof(out[2].c_str()) - 1]});
		}
		for (int ii = 0; ii < VertexFound.size(); ii++)
		{
			IndecesFound.push_back(ii);
		}
		this->set(VertexFound, IndecesFound);
	
	}
private:
	void ReturnStringArray(std::string const &str, const char delim, std::vector<std::string> &out)
	{
		int start;
		int end = 0;
		while((start = str.find_first_not_of(delim, end)) != std::string::npos)
		{
			end = str.find(delim, start);
			out.push_back(str.substr(start, end - start));
		}
	}
	static enum StringValue
	{
		V =1,
		VT,
		VN,
		F
	 };
	std::map<std::string, StringValue> StringFound;
	void InitStringZFound()
	{
		StringFound["v"] = V;
		StringFound["vt"] = VT;
		StringFound["vn"] = VN;
		StringFound["f"] = F;
	}
};

class Sphere_M :public Primitive
{
public:

	Sphere_M(float Radius, float SectorCount, float StackCount)
		:Primitive()
	{
		std::vector<GLuint> TempIndices;
		std::vector<Vertex> TempVertex;
		glm::vec3 Clr = glm::vec3(1, 0, 1);
		float Z, XY;								// Vertex Position
		float lengthInv = 1.f / Radius;		// Vertex normal
		float PI = glm::pi<float>();
		float SectorStep = 2 * PI / SectorCount;
		float StackStep = PI / StackCount;
		float SectorAngle, StackAngle;
		for (int ii = 0; ii <= StackCount; ii++)
		{
			StackAngle = PI / 2 - ii * StackStep;
			XY = Radius * (float)glm::cos(StackAngle);
			Z = Radius * (float)glm::sin(StackAngle);
						
			for (int jj = 0; jj <= SectorCount; jj++)
			{
				Vertex Temp;
				SectorAngle = jj * SectorStep;

				Temp.position.x = XY * (float)glm::sin(SectorAngle);
				Temp.position.z = Z;
				Temp.position.y = XY * (float)glm::cos(SectorAngle);
				
				Temp.normal.x = Temp.position.x * lengthInv;
				Temp.normal.y = Temp.position.y * lengthInv;
				Temp.normal.z = Temp.position.z * lengthInv;

				Temp.texcoord.x = (float)ii / SectorCount;

				Temp.texcoord.y = (float)jj / SectorCount;

				TempVertex.push_back(Temp);
			}
		}
		int K1, K2;
		for (int ii = 0; ii < StackCount; ii++)
		{
			K1 = ii * (SectorCount + 1);
			K2 = K1 + SectorCount + 1;
			for (int jj = 0; jj < SectorCount; jj++, K1++, K2++)
			{
				if (ii != 0)
				{
					TempIndices.push_back(K2);
					TempIndices.push_back(K1);
					TempIndices.push_back(K1 +1);
				}

				if (ii != (StackCount - 1))
				{
					TempIndices.push_back(K2);
					TempIndices.push_back(K1 +1);
					TempIndices.push_back(K2 + 1);
				}
			}

		}
		this->set(TempVertex, TempIndices);
	}
};

class Cylinder_M : public Primitive
{
public:
	Cylinder_M(float Radius, int Height, int SectorCount)
		:Primitive()
	{
		std::vector<Vertex> TempVertex;
		std::vector<GLuint> TempIndices;
		glm::vec3 Clr = glm::vec3(1.f, 1.f, 1.f);
		float PI = glm::pi<float>();
		float SectorStep = 2.f * PI / SectorCount;
		for (int ii = 0; ii <= Height ; ii++)
		{
			for (int jj = 0; jj <= SectorCount; jj++)
			{
				Vertex VertexFound;
				VertexFound.position.z = ii;
				VertexFound.position.y = Radius * (float)glm::cos((float)jj * SectorStep); 
				VertexFound.position.x = Radius * (float)glm::sin((float)jj * SectorStep);

				VertexFound.normal.z = 0;
				VertexFound.normal.y = VertexFound.position.z / Radius;
				VertexFound.normal.x = VertexFound.position.x / Radius;

				VertexFound.texcoord.x = ii/ Height;
				VertexFound.texcoord.y = jj/ SectorCount;
				TempVertex.push_back(VertexFound);
			}
		}
		
		for (int jj = 0; jj < Height; jj++)
		{
			for (int ii = 0; ii <= SectorCount-1; ii++)
			{
				GLuint TopLeft = ((jj + 1) * (SectorCount+1)) + ii;
				GLuint TopRight = TopLeft + 1;
				GLuint BottomLeft = ((jj) * (SectorCount+1)) + ii;
				GLuint BottomRight = BottomLeft + 1;
				TempIndices.push_back(TopLeft);
				TempIndices.push_back(BottomLeft);
				TempIndices.push_back(TopRight);
				TempIndices.push_back(TopRight);
				TempIndices.push_back(BottomLeft);
				TempIndices.push_back(BottomRight);
			}
		}
		this->set(TempVertex, TempIndices);
	}
};

class Cone_M : public Primitive
{
public:
	Cone_M(float Height,float Radius,int SectorCount, int HeightDiv)
		:Primitive()
	{
		std::vector<Vertex> TempVertex;
		std::vector<GLuint> TempIndices;
		glm::vec3 Clr = glm::vec3(1.f, 1.f, 1.f);
		float PI = glm::pi<float>();
		float SectorStep = 2.f * PI / SectorCount;
		float DivStep = Height / HeightDiv;
		for (int ii = 0; ii <= HeightDiv; ii++)
		{
			float ConeRadius = (Height - (ii * DivStep /Height)) * (Radius / Height);
			for (int jj = 0; jj <= SectorCount; jj++)
			{
				Vertex VertexFound;
				VertexFound.position.z = ii * DivStep;
				VertexFound.position.x = ConeRadius * (float)glm::sin((float)jj * SectorStep);
				VertexFound.position.y = ConeRadius * (float)glm::cos((float)jj * SectorStep);

				VertexFound.normal.z = 0;
				VertexFound.normal.x = VertexFound.position.x / ConeRadius;
				VertexFound.normal.y = VertexFound.position.z / ConeRadius;

				VertexFound.texcoord.x = ii / HeightDiv;
				VertexFound.texcoord.y = jj / SectorCount;

				TempVertex.push_back(VertexFound);
			}
		}
		for (int jj = 0; jj < HeightDiv; jj++)
		{
			for (int ii = 0; ii <= SectorCount - 1; ii++)
			{
				GLuint TopLeft = ((jj + 1) * (SectorCount + 1)) + ii;
				GLuint TopRight = TopLeft + 1;
				GLuint BottomLeft = ((jj) * (SectorCount + 1)) + ii;
				GLuint BottomRight = BottomLeft + 1;
				TempIndices.push_back(TopLeft);
				TempIndices.push_back(BottomLeft);
				TempIndices.push_back(TopRight);
				TempIndices.push_back(TopRight);
				TempIndices.push_back(BottomLeft);
				TempIndices.push_back(BottomRight);
			}
		}
		this->set(TempVertex, TempIndices);
	}
};

class ASSIMPLOAD_M
{
private:
	glm::mat4 aiMatToglmMat(aiMatrix4x4 aiVal)
	{
		glm::mat4 glmVal = glm::mat4(aiVal.a1, aiVal.b1, aiVal.c1, aiVal.d1,
			aiVal.a2, aiVal.b2, aiVal.c2, aiVal.d2,
			aiVal.a3, aiVal.b3, aiVal.c3, aiVal.d3,
			aiVal.a4, aiVal.b4, aiVal.c4, aiVal.d4);
		return glmVal;
	}
	glm::vec3 aiVecToglmVec(aiVector3D aiVal)
	{
		return glm::vec3(aiVal.x, aiVal.y, aiVal.z);
	}
	std::vector<Vertex> FinalVertex(const aiMesh* Meshes)
	{
		std::vector<Vertex> TempVerts;
		for (int ii = 0; ii < Meshes->mNumVertices; ii++)
		{
			Vertex NewVertex{};
			//Position
			NewVertex.position.x = Meshes->mVertices[ii].x;
			NewVertex.position.y = Meshes->mVertices[ii].y;
			NewVertex.position.z =  Meshes->mVertices[ii].z;
			//Normals
			NewVertex.normal.x = Meshes->mNormals[ii].x;
			NewVertex.normal.y = Meshes->mNormals[ii].y;
			NewVertex.normal.z =  Meshes->mNormals[ii].z;
			//Texture Coordinates
			NewVertex.texcoord.x = Meshes->mTextureCoords[0][ii].x;
			NewVertex.texcoord.y = Meshes->mTextureCoords[0][ii].y;
			TempVerts.push_back(NewVertex);
		}
		return TempVerts;
	}
	std::vector<GLuint> FinalGluint(const aiMesh* Meshes)
	{
		std::vector<GLuint> TempInd;
		for (int ii = 0; ii < Meshes->mNumFaces; ii++)
		{
			aiFace face = Meshes->mFaces[ii];
			TempInd.push_back(face.mIndices[0]);
			TempInd.push_back(face.mIndices[1]);
			TempInd.push_back(face.mIndices[2]);
		}
		return TempInd;
	}
	std::string File;
public:
	ASSIMPLOAD_M(const char* FileLoc)
	{
		File = "Models/ModelCol/";
		File += FileLoc;
	}
	Vec_UP<Primitive> GetModels(glm::mat4& inv)
	{
		Vec_UP<Primitive> Mshs;
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(File, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_FlipUVs);
		if (!scene)
		{
			std::cout << "Error";
			return Mshs;
		}
		int Amount_Mshs = scene->mNumMeshes;
		for (int ii = 0; ii < Amount_Mshs; ii++)
		{
			Mshs.push_back(std::make_unique<Primitive>());
			Mshs[ii]->set(this->FinalVertex(scene->mMeshes[ii]), this->FinalGluint(scene->mMeshes[ii]));
			int bnCount = scene->mMeshes[ii]->mNumBones;
			std::cout << bnCount;
			std::cout << "\n";
		}
		inv =  this->aiMatToglmMat(scene->mRootNode->mTransformation);
		return Mshs;
	}
};

class Capsule_M :public Primitive
{
public:
	Capsule_M(float Rad,float Length,
		float SectorCount, float StackCount)
		:Primitive()
	{
		std::vector<GLuint> TempIndices;
		std::vector<Vertex> TempVertex;
		//Top of the Capsule
		glm::vec3 Clr = glm::vec3(1, 0, 1);
		float Z, XY;								// Vertex Position
		float lengthInv = 1.f / Rad;		// Vertex normal
		float PI = glm::pi<float>();
		float SectorStep = 2 * PI / SectorCount;
		float StackStep = PI / StackCount;
		float SectorAngle, StackAngle;
		for (int ii = 0; ii <= StackCount; ii++)
		{
			StackAngle = (PI/2 - (ii * StackStep));
			XY = Rad * (float)glm::cos(StackAngle);
			Z = Rad * (float)glm::sin(StackAngle);

			for (int jj = 0; jj <= SectorCount; jj++)
			{
				Vertex Temp;
				SectorAngle = jj * SectorStep;

				Temp.position.x = XY * (float)glm::sin(SectorAngle);
				Temp.position.z = Z;
				Temp.position.y = XY * (float)glm::cos(SectorAngle);

				Temp.normal.x = Temp.position.x * lengthInv;
				Temp.normal.y = Temp.position.y * lengthInv;
				Temp.normal.z = Temp.position.z * lengthInv;

				if (StackAngle > 0)
					Temp.position.z += (Length / 2);
				else
					Temp.position.z -= (Length / 2);

				Temp.texcoord.x = (float)ii / SectorCount;

				Temp.texcoord.y = (float)jj / SectorCount;

				TempVertex.push_back(Temp);
			}
		}
		int K1, K2;
		for (int ii = 0; ii < StackCount; ii++)
		{
			K1 = ii * (SectorCount + 1);
			K2 = K1 + SectorCount + 1;
			for (int jj = 0; jj < SectorCount; jj++, K1++, K2++)
			{
				if (ii != 0)
				{
					TempIndices.push_back(K2);
					TempIndices.push_back(K1);
					TempIndices.push_back(K1 + 1);
				}

				if (ii != (StackCount - 1))
				{
					TempIndices.push_back(K2);
					TempIndices.push_back(K1 + 1);
					TempIndices.push_back(K2 + 1);
				}
			}

		}
		//Body of capsules

		//Bottom of Capsule
		this->set(TempVertex, TempIndices);
	}
};