#include "Mesh.hpp"

#include <iostream>

namespace sfew
{
	// Ctor/Dtor ========================================

	Mesh::Mesh(const std::vector<float>& newVertexDataArray) : INameable("Unnamed Mesh")
	{
		// Create a vertex buffer object to hold vertex data
		glGenBuffers(1, &_vbo);

		// Make it the current active buffer
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

		// Send the vertex data into the graphics card
		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBufferData(GL_ARRAY_BUFFER, newVertexDataArray.size() * sizeof(float), newVertexDataArray.data(), GL_STATIC_DRAW);
	}

	Mesh::~Mesh()
	{
		// Delete the vertex buffer object
		glDeleteBuffers(1, &_vbo);
	}

	// Routines =========================================

	// Properties =========================================

	// Helpers =========================================
}