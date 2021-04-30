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
	std::vector<AnimVertex> vertices;
	std::vector<GLuint> indices;

public:
	Primitive()
	{

	}
	virtual ~Primitive()
	{

	}
	void set(const AnimVertex* vertices, const unsigned nrofVertices,
		const GLuint* indices, const unsigned nrOfIndices)
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
	void set(std::vector<AnimVertex> vertexFound, std::vector<GLuint> indicesFound)
	{
		this->vertices = vertexFound;
		this->indices = indicesFound;
	}
	inline AnimVertex* getVertices() { return this->vertices.data(); }
	inline GLuint* getIndices() { return this->indices.data(); }

	inline const unsigned getNrOfVertices() { return this->vertices.size(); }
	inline const unsigned getNrOfIndices() { return this->indices.size(); }

};