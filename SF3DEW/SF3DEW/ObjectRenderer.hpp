// Object Renderer
// Draws a mesh-material pairing (single 3D object)
//
// Written by Jibran Syed (4-13-2014)

#ifndef SFEW_OBJECT_RENDERER_H
#define SFEW_OBJECT_RENDERER_H

#include <memory>
#include <SFML/System/NonCopyable.hpp>

#include "Mesh.hpp"
#include "Material.hpp"

namespace sfew
{
	class ObjectRenderer : sf::NonCopyable
	{
	public:

		// Ctor/Dtor ======================

		ObjectRenderer();
		ObjectRenderer(std::weak_ptr<Mesh> mesh);
		ObjectRenderer(std::weak_ptr<Material> material);
		ObjectRenderer(std::weak_ptr<Mesh> mesh, std::weak_ptr<Material> material);
		~ObjectRenderer();

		// Routines =======================

		void Draw();				// Draws the 3D entity

		// Properties =====================

	private:

		// Helpers ========================

		bool validateMesh() const;			// Does mesh pointer still exist?
		bool validateMaterial() const;		// Does material pointer still exist?

		// Data ===========================

		std::weak_ptr<Mesh> _mesh;					// The mesh being referenced
		std::weak_ptr<Material> _material;			// The material being referenced
		std::shared_ptr<Mesh> _blankMesh;			// Strong reference to a blank mesh
		std::shared_ptr<Material> _blankMaterial;	// Strong reference to a blank material

	};

	
} // namespace sfew

#endif