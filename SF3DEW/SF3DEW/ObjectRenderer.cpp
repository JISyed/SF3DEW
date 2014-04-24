#include "ObjectRenderer.hpp"

#include <iostream>
#include <GL/glew.h>	// For glDrawArrays()

#define START_AT_FIRST_VERTEX 0

namespace sfew
{
	// Ctor/Dtor ========================================

	// Default Ctor
	ObjectRenderer::ObjectRenderer() :
		_isPersistant(false)
	{
		// Make a default mesh and assign it
		_blankMesh = std::shared_ptr<Mesh>(new Mesh());
		_mesh = _blankMesh;

		// Make a default material and assign it
		_blankMaterial = std::shared_ptr<Material>(new Material());
		_material = _blankMaterial;
	}

	// Mesh Ctor
	ObjectRenderer::ObjectRenderer(std::weak_ptr<Mesh> mesh) :
		_mesh(mesh),
		_isPersistant(false)
	{
		// Make a default material and assign it
		_blankMaterial = std::shared_ptr<Material>(new Material());
		_material = _blankMaterial;
	}

	// Material Ctor
	ObjectRenderer::ObjectRenderer(std::weak_ptr<Material> material) :
		_material(material),
		_isPersistant(false)
	{
		// Make a default mesh and assign it
		_blankMesh = std::shared_ptr<Mesh>(new Mesh());
		_mesh = _blankMesh;
	}

	// Mesh and Material Ctor
	ObjectRenderer::ObjectRenderer(std::weak_ptr<Mesh> mesh, std::weak_ptr<Material> material) :
		_mesh(mesh),
		_material(material),
		_isPersistant(false)
	{
		
	}

	// Dtor
	ObjectRenderer::~ObjectRenderer()
	{
		
	}

	// Routines =========================================

	void ObjectRenderer::Draw()
	{
		// Make sure pointers are valid
		if(!validateMesh()) return;
		if(!validateMaterial()) return;

		// Make the referenced mesh and material active
		_mesh._Get()->MakeActiveMeshToDraw();
		_material._Get()->Use();

		// Send the latest model matrix down the shader
		_material._Get()->SetUniform("model", _modelMatrix);

		// Draw the object
		glDrawArrays(GL_TRIANGLES, 
					 START_AT_FIRST_VERTEX, 
					 _mesh._Get()->GetNumberOfVertices()
		);
	}

	// Get the latest model matrix from a Transform
	void ObjectRenderer::UpdateModelMatrix(Matrix4 newMatrix)
	{
		if(!validateMaterial()) return;

		_modelMatrix = newMatrix;
	}

	// Properties =========================================

	void ObjectRenderer::SetMesh(std::weak_ptr<Mesh> newMesh)
	{
		_mesh = newMesh;
	}

	std::weak_ptr<Mesh> ObjectRenderer::GetMesh() const
	{
		return _mesh;
	}

	void ObjectRenderer::SetMaterial(std::weak_ptr<Material> newMaterial)
	{
		_material = newMaterial;
	}

	std::weak_ptr<Material> ObjectRenderer::GetMaterial() const
	{
		return _material;
	}

	// Helpers =========================================

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
	
	void ObjectRenderer::SetPersistance(bool willBePersistant)
	{
		_isPersistant = willBePersistant;
	}

	bool ObjectRenderer::IsPersistant() const
	{
		return _isPersistant;
	}

} // namespace sfew