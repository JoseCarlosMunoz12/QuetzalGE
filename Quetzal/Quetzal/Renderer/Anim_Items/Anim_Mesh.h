#pragma once

#include <iostream>
#include <vector>

#include "../Render_Items/Vertex.h"
#include "../Render_Items/Shader.h"
#include "../Render_Items/Texture.h"
#include "Anim_Primitive.h"

class Anim_Mesh
{

private:
	AnimVertex* vertexArray;
	GLuint* indexArray;
	std::vector<AnimVertex> VertexTofind;
	unsigned nrOfVertices;
	unsigned nrOfIndices;
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	std::string NameOfMesh;
	glm::mat4 Inv = glm::mat4(1.f);
	void InitVAO()
	{
		//Create VAO
		glCreateVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);

		//GEN VBO AND BIND AND SEND DATA

		glGenBuffers(1, &this->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, this->nrOfVertices * sizeof(AnimVertex), this->vertexArray, GL_STATIC_DRAW);

		//GEN EBO and BIND And Send Data---------
		if (this->nrOfIndices > 0)
		{
			glGenBuffers(1, &this->EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->nrOfIndices * sizeof(GLuint), this->indexArray, GL_STATIC_DRAW);
		}

		//Set VerttexAttribPointers and Enable (input assembly)
		//Position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(AnimVertex), (GLvoid*)offsetof(AnimVertex, position));
		glEnableVertexAttribArray(0);
		//TexCoord
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(AnimVertex), (GLvoid*)offsetof(AnimVertex, texcoord));
		glEnableVertexAttribArray(1);
		//Normal
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(AnimVertex), (GLvoid*)offsetof(AnimVertex, normal));
		glEnableVertexAttribArray(2);
		//MatId
		glVertexAttribPointer(3, 3, GL_INT  , GL_FALSE, sizeof(AnimVertex), (GLvoid*)offsetof(AnimVertex, MatId));
		glEnableVertexAttribArray(3);
		//Weights
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(AnimVertex), (GLvoid*)offsetof(AnimVertex, Weights));
		glEnableVertexAttribArray(4);
		//BIND VAO 0
		glBindVertexArray(0);
	}
	void updateUniforms(glm::mat4 FinalMatrix, std::shared_ptr<Shader> shader)
	{
		shader->setMat4fv(FinalMatrix, "ModelMatrix");
	}
public:
	Anim_Mesh(std::unique_ptr<A_Primitive> primitive,
		std::string Name)
	{
		this->NameOfMesh = Name;

		this->nrOfIndices = primitive->getNrOfIndices();
		this->nrOfVertices = primitive->getNrOfVertices();
		this->vertexArray = new AnimVertex[this->nrOfVertices];
		for (size_t i = 0; i < this->nrOfVertices; i++)
		{
			this->vertexArray[i] = primitive->getVertices()[i];
			VertexTofind.push_back(vertexArray[i]);
		}
		this->indexArray = new GLuint[this->nrOfIndices];
		for (size_t i = 0; i < this->nrOfIndices; i++)
		{
			this->indexArray[i] = primitive->getIndices()[i];
		}

		this->InitVAO();
	}
	Anim_Mesh(AnimVertex* VertexArray,
		std::string Name,
		const unsigned& nrOfVertices, GLuint* indexArray,
		const unsigned& nrOfIndices)
	{
		this->NameOfMesh = Name;

		this->nrOfIndices = nrOfIndices;
		this->nrOfVertices = nrOfVertices;
		this->vertexArray = new AnimVertex[this->nrOfVertices];
		for (size_t i = 0; i < nrOfVertices; i++)
		{
			this->vertexArray[i] = VertexArray[i];
			VertexTofind.push_back(vertexArray[i]);
		}
		this->indexArray = new GLuint[this->nrOfIndices];
		for (size_t i = 0; i < nrOfIndices; i++)
		{
			this->indexArray[i] = indexArray[i];
		}
		this->InitVAO();
	}
	Anim_Mesh(const Anim_Mesh& obj)
	{
		this->NameOfMesh = obj.NameOfMesh;
		this->nrOfIndices = obj.nrOfIndices;
		this->nrOfVertices = obj.nrOfVertices;
		this->vertexArray = new AnimVertex[this->nrOfVertices];
		for (size_t i = 0; i < nrOfVertices; i++)
		{
			this->vertexArray[i] = obj.vertexArray[i];
			VertexTofind.push_back(vertexArray[i]);
		}
		this->indexArray = new GLuint[this->nrOfIndices];
		for (size_t i = 0; i < nrOfIndices; i++)
		{
			this->indexArray[i] = obj.indexArray[i];
		}
		this->InitVAO();
	}

	~Anim_Mesh()
	{
		glDeleteVertexArrays(1, &this->VAO);
		glDeleteBuffers(1, &this->VBO);
		if (this->nrOfIndices > 0)
		{
			glDeleteBuffers(1, &this->EBO);
		}
		delete[] this->vertexArray;
		delete[] this->indexArray;
	}
	//Accessors
	void Render(glm::mat4 FinalMatrix, std::shared_ptr<Shader> shader)
	{
		//Update Uniforms
		this->updateUniforms(FinalMatrix, shader);
		shader->use();
		//BInd VAO
		glBindVertexArray(this->VAO);
		//Render
		if (this->nrOfIndices == 0)
		{
			glDrawArrays(GL_TRIANGLES, 0, this->nrOfVertices);
		}
		else
		{
			glDrawElements(GL_TRIANGLES, this->nrOfIndices, GL_UNSIGNED_INT, 0);
		}
		//Clean up
		glBindVertexArray(0);
		glUseProgram(0);
		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	const char* GiveName()
	{
		return this->NameOfMesh.c_str();
	}
	void SetInv(glm::mat4 InitInv)
	{
		Inv = InitInv;
	}
	glm::mat4 GetInv()
	{
		return this->Inv;
	}
};