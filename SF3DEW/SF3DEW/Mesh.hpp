// Mesh
// Abstraction for mesh data and vertex buffer objects
//
// Written by Jibran Syed (4-6-2014)

#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <SFML/System/NonCopyable.hpp>
#include <vector>

#include "INameable.hpp"

namespace sfew
{
	class Mesh : sf::NonCopyable, public INameable
	{
	public:

		// Ctor/Dtor ======================

		Mesh();
		Mesh(const std::vector<float>& newVertexDataArray);
		virtual ~Mesh();

		// Routines =======================

		void MakeActiveMeshToDraw();	// Make active mesh to draw
		static void StopUsingMeshes();	// Makes no mesh the active mesh

		// Properties =====================

		int GetNumberOfVertices() const;

	private:

		// Data ===========================

		GLuint _vao;		// Handle to vertex format
		GLuint _vbo;		// Handle to vertex data in shader
		int _numberOfVerts;	// Total number of vertices in mesh

	};

	
} // namespace sfew

#endif