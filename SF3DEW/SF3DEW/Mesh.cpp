#include "Mesh.hpp"

#include <iostream>

namespace sfew
{
	// Ctor/Dtor ========================================

	// Default Ctor
	Mesh::Mesh() : INameable("Default Cube Mesh")
	{
		// CUBE
		GLfloat vertices[] = {
			// X     Y      Z     R     G     B     A     U     V
			// Back
			 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // TL 1 1
			 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // BL 1 0
			-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // BR 0 0
			-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // BR 0 0
			-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // TR 0 1
			 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // TL 1 1
		
			// Front
			-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // BL
			 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // BR
			 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // TR
			 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // TR
			-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // TL
			-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // BL

			// Left
			-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // TL 0 1
			-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // TR 1 1
			-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // BR 1 0
			-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // BR 1 0
			-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // BL 0 0
			-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // TL 0 1
		
			// Right
			 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // BR
			 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // TR
			 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // TL
			 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // TL
			 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // BL
			 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // BR

			// Down
			-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // M 0 1
			 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // K 1 1
			 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // J 1 0
			 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // J 1 0
			-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // L 0 0
			-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // M 0 1

			// Up
			 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f
		};

		// Create a vertex array object for storing the vertex format
		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);

		// Create a vertex buffer object to hold vertex data
		glGenBuffers(1, &_vbo);

		// Make it the current active buffer
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

		// Send the vertex data into the graphics card
		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBufferData(GL_ARRAY_BUFFER, 324 * sizeof(float), vertices, GL_STATIC_DRAW);

		// Calculate the total number of vertices
		// This assumes vertex data is 9 floats long!!!
		// See Shader::formatVertexAttributes()
		_numberOfVerts = 324 / 9;
	}

	// Ctor
	Mesh::Mesh(const std::vector<float>& newVertexDataArray) : INameable("Unnamed Mesh")
	{
		// Create a vertex array object for storing the vertex format
		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);

		// Create a vertex buffer object to hold vertex data
		glGenBuffers(1, &_vbo);

		// Make it the current active buffer
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

		// Send the vertex data into the graphics card
		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBufferData(GL_ARRAY_BUFFER, newVertexDataArray.size() * sizeof(float), newVertexDataArray.data(), GL_STATIC_DRAW);

		// Calculate the total number of vertices
		// This assumes vertex data is 9 floats long!!!
		// See Shader::formatVertexAttributes()
		_numberOfVerts = newVertexDataArray.size() / 9;
	}

	// Dtor
	Mesh::~Mesh()
	{
		// Delete the vertex buffer object
		glDeleteBuffers(1, &_vbo);

		// Delete the vertex array object
		glDeleteVertexArrays(1, &_vao);
	}

	// Routines =========================================

	// Make active mesh to draw
	void Mesh::MakeActiveMeshToDraw()
	{
		glBindVertexArray(_vao);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	}

	// Makes no mesh the active mesh
	void Mesh::StopUsingMeshes()
	{
		glBindVertexArray(NULL);
		glBindBuffer(GL_ARRAY_BUFFER, NULL);
	}

	// Properties =========================================

	int Mesh::GetNumberOfVertices() const
	{
		return _numberOfVerts;
	}

} // namespace sfew