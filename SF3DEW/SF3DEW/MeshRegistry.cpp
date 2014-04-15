#include "MeshRegistry.hpp"

#include <iostream>
#include <SFML/System.hpp>

#include "ShaderRegistry.hpp"

namespace sfew
{
	// Static data ========================================

	MeshRegistry* MeshRegistry::_instance = NULL;

	// Ctor/Dtor ========================================

	// Ctor
	MeshRegistry::MeshRegistry()
	{
		if(MeshRegistry::_instance != NULL)
		{
			std::cout << "ERROR: MeshRegistry being instantiated more than once!\n";
			std::cout << "Aborting in 11 seconds...";

			sf::sleep(sf::seconds(11.0f));

			exit(1);
		}

		// Assign the internal singleton
		MeshRegistry::_instance = this;
	}

	// Dtor
	MeshRegistry::~MeshRegistry()
	{
		// Clear the internal singleton
		MeshRegistry::_instance = NULL;
	}

	// Routines =========================================

	// Load all the resources
	bool MeshRegistry::Load()
	{
		// Load the builtin meshes
		loadCube();
		loadTetrahedron();
		loadOctohedron();
		loadPrism();

		// Assumes that the resources were successfully loaded
		_resourcesLoaded = true;

		return _resourcesLoaded;
	}

	// Unload all the resources
	void MeshRegistry::Unload()
	{
		// Skip unloading of list if empty
		if(_resourceList.empty()) return;

		// Empty the list
		_resourceList.clear();

		// Mark the resources as unloaded
		_resourcesLoaded = false;
	}

	// Sets up every mesh's VAO with every shader
	void MeshRegistry::SetupAllVertexFormats()
	{
		// Make sure the ShaderRegistry exists
		// Everything afterward requires MeshRegistry to be ShaderRegistry's friend
		if(ShaderRegistry::_instance == NULL) return;

		// For every shader...
		for(const auto& shader : ShaderRegistry::_instance->_resourceList)
		{
			// ... Make it active.
			shader->UseShader();

			// Then for every mesh ...
			for(const auto& mesh : _resourceList)
			{
				// ... Make it active as well ...
				mesh->MakeActiveMeshToDraw();

				// And set up the shader's vertex format with the mesh's VAO.
				shader->FormatVertexAttributes();
			}
		}
	}

	// Properties =========================================

	// STATIC: Returns a weak reference to an object by name
	std::weak_ptr<Mesh> MeshRegistry::GetByName(const std::string& name)
	{
		// Make sure this registry exists
		std::weak_ptr<Mesh> empty = std::weak_ptr<Mesh>();
		if(!MeshRegistry::verifyInstantiation()) return empty;
		if(MeshRegistry::_instance->_resourceList.empty()) return empty;

		// Search through the list for an object with the same name as queried
		std::weak_ptr<Mesh> foundObject = std::weak_ptr<Mesh>();
		for(auto& resource : MeshRegistry::_instance->_resourceList)
		{
			// Are the two name string the same?
			if(resource->GetName().compare(name) == 0)
			{
				foundObject = resource;
				return foundObject;
			}
		}

		// Couldn't find the queried name
		return empty;
	}

	// Helpers =========================================

	// STATIC: Was this object instantiated?
	bool MeshRegistry::verifyInstantiation()
	{
		if(MeshRegistry::_instance == NULL)
		{
			std::cout << "ERROR: MeshRegistry not instantiated!" << std::endl;
			return false;
		}

		return true;
	}

	// Load the cube mesh
	void MeshRegistry::loadCube()
	{
		// Cube Mesh
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
		
		// Create vertex buffer for mesh
		std::vector<float> vertexData(vertices, vertices + sizeof(vertices) / sizeof(float));

		// Pass the buffer into a new Mesh object
		std::shared_ptr<Mesh> newMesh(new Mesh(vertexData));
		newMesh->SetName("CubeMesh");

		// Add the Mesh to the list
		_resourceList.push_front(newMesh);
	}

	// Load the tetrahedrion mesh
	void MeshRegistry::loadTetrahedron()
	{
		// Tetrahedron Mesh
		GLfloat vertices[] = {
			-0.5f, -0.3f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,	// L
			 0.0f,  0.3f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f,	// T
			 0.5f, -0.3f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,	// R

			-0.5f, -0.3f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,	// L
			 0.0f,  0.0f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f,	// F
			 0.0f,  0.3f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,	// T

			 0.0f,  0.0f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f,	// F
			 0.5f, -0.3f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,	// R
			 0.0f,  0.3f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,	// T

			-0.5f, -0.3f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,	// L
			 0.5f, -0.3f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,	// R
			 0.0f,  0.0f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 5.0f, 1.0f		// F
		};

		// Create vertex buffer for mesh
		std::vector<float> vertexData(vertices, vertices + sizeof(vertices) / sizeof(float));

		// Pass the buffer into a new Mesh object
		std::shared_ptr<Mesh> newMesh(new Mesh(vertexData));
		newMesh->SetName("TetrahedronMesh");

		// Add the Mesh to the list
		_resourceList.push_front(newMesh);
	}

	// Load the octohedron mesh
	void MeshRegistry::loadOctohedron()
	{
		// Octohedron
		GLfloat vertices[] = {
			 0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f,
			 0.0f,  0.8f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.25f, 1.0f,
			 0.0f,  0.0f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f,  0.0f,

			-0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f,  0.0f,
			 0.0f,  0.0f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f,
			 0.0f,  0.8f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.25f, 1.0f,

			 0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f,
			 0.0f,  0.0f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f,  0.0f,
			 0.0f,  0.8f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.25f, 1.0f,

			-0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f,  0.0f,
			 0.0f,  0.8f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.25f, 1.0f,
			 0.0f,  0.0f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f,

			 0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f,
			 0.0f,  0.0f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f,  0.0f,
			 0.0f, -0.8f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.25f, 1.0f,

			-0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f,  0.0f,
			 0.0f, -0.8f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.25f, 1.0f,
			 0.0f,  0.0f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f,

			 0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f,
			 0.0f, -0.8f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.25f, 1.0f,
			 0.0f,  0.0f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f,  0.0f,

			-0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f,
			 0.0f,  0.0f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f,  0.0f,
			 0.0f, -0.8f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.25f, 1.0f
		};

		// Create vertex buffer for mesh
		std::vector<float> vertexData(vertices, vertices + sizeof(vertices) / sizeof(float));

		// Pass the buffer into a new Mesh object
		std::shared_ptr<Mesh> newMesh(new Mesh(vertexData));
		newMesh->SetName("OctohedronMesh");

		// Add the Mesh to the list
		_resourceList.push_front(newMesh);
	}

	// Load the triangular prism mesh
	void MeshRegistry::loadPrism()
	{
		// Triangular Prism
		GLfloat vertices[] = {
			-0.5f,  0.5f,  0.1f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // LO 
			 0.0f, -1.4f,  0.1f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f, // BO
			 0.5f,  0.5f,  0.1f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // RO

			-0.5f,  0.5f, -0.1f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // LI
			 0.5f,  0.5f, -0.1f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // RI
			 0.0f, -1.4f, -0.1f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f, // BI

			-0.5f,  0.5f,  0.1f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // LO
			-0.5f,  0.5f, -0.1f, 1.0f, 1.0f, 1.0f, 1.0f, 0.2f, 1.0f, // LI
			 0.0f, -1.4f,  0.1f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // BO

			-0.5f,  0.5f, -0.1f, 1.0f, 1.0f, 1.0f, 1.0f, 0.2f, 1.0f, // LI
			 0.0f, -1.4f, -0.1f, 1.0f, 1.0f, 1.0f, 1.0f, 0.2f, 0.0f, // BI
			 0.0f, -1.4f,  0.1f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // BO

			 0.0f, -1.4f,  0.1f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // BO
			 0.5f,  0.5f, -0.1f, 1.0f, 1.0f, 1.0f, 1.0f, 0.2f, 1.0f, // RI
			 0.5f,  0.5f,  0.1f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // RO

			 0.0f, -1.4f,  0.1f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // BO
			 0.0f, -1.4f, -0.1f, 1.0f, 1.0f, 1.0f, 1.0f, 0.2f, 0.0f, // BI
			 0.5f,  0.5f, -0.1f, 1.0f, 1.0f, 1.0f, 1.0f, 0.2f, 1.0f, // RI

			-0.5f,  0.5f,  0.1f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // LO
			 0.5f,  0.5f,  0.1f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // RO
			 0.5f,  0.5f, -0.1f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.2f, // RI

			 0.5f,  0.5f, -0.1f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.2f, // RI
			-0.5f,  0.5f, -0.1f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.2f, // LI
			-0.5f,  0.5f,  0.1f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f  // LO 
		};

		// Create vertex buffer for mesh
		std::vector<float> vertexData(vertices, vertices + sizeof(vertices) / sizeof(float));

		// Pass the buffer into a new Mesh object
		std::shared_ptr<Mesh> newMesh(new Mesh(vertexData));
		newMesh->SetName("PrismMesh");

		// Add the Mesh to the list
		_resourceList.push_front(newMesh);
	}


} // namespace sfew