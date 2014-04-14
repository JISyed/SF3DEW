#include "ObjectRenderer.hpp"

#include <iostream>

namespace sfew
{
	// Ctor/Dtor ========================================

	// Default Ctor
	ObjectRenderer::ObjectRenderer()
	{
		// Make a default mesh and assign it
		_blankMesh = std::shared_ptr<Mesh>(new Mesh());
		_mesh = _blankMesh;

		// Make a default material and assign it
		_blankMaterial = std::shared_ptr<Material>(new Material());
		_material = _blankMaterial;
	}

	ObjectRenderer::ObjectRenderer(std::weak_ptr<Mesh> mesh) :
		_mesh(mesh)
	{
		// Make a default material and assign it
		_blankMaterial = std::shared_ptr<Material>(new Material());
		_material = _blankMaterial;
	}

	ObjectRenderer::ObjectRenderer(std::weak_ptr<Material> material) :
		_material(material)
	{
		// Make a default mesh and assign it
		_blankMesh = std::shared_ptr<Mesh>(new Mesh());
		_mesh = _blankMesh;
	}

	ObjectRenderer::ObjectRenderer(std::weak_ptr<Mesh> mesh, std::weak_ptr<Material> material) :
		_mesh(mesh),
		_material(material)
	{
		
	}

	// Dtor
	ObjectRenderer::~ObjectRenderer()
	{
		// Make sure pointers are valid
		if(!validateMesh()) return;
		if(!validateMaterial()) return;

		// Make the referenced mesh and material active
		_mesh._Get()->MakeActiveMeshToDraw();
		_material._Get()->Use();
	}

	// Routines =========================================

	// Properties =========================================

	// Does mesh pointer still exist?
	bool ObjectRenderer::validateMesh() const
	{
		if(_mesh.expired())
		{
			std::cout << "Error: ObjectRenderer doesn't have a mesh!" << std::endl;
			return false;
		}

		return true;
	}

	// Does material pointer still exist?
	bool ObjectRenderer::validateMaterial() const
	{
		if(_material.expired())
		{
			std::cout << "Error: ObjectRenderer doesn't have a material!" << std::endl;
			return false;
		}

		return true;
	}

	// Helpers =========================================

} // namespace sfew