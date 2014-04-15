// Mesh Registry
// A registry for store all Mesh objects
//
// Written by Jibran Syed (4-14-2014)

#ifndef SFEW_MESH_REGISTRY_H
#define SFEW_MESH_REGISTRY_H

#include "Registry.hpp"
#include "Mesh.hpp"

namespace sfew
{
	class MeshRegistry : public Registry
	{
	public:

		// Ctor/Dtor ======================

		MeshRegistry();
		virtual ~MeshRegistry();

		// Routines =======================

		virtual bool Load();						// Load all the resources
		virtual void Unload();						// Unload all the resources
		void SetupAllVertexFormats();				// Sets up every mesh's VAO with every shader

		// Properties =====================

		static std::weak_ptr<Mesh> GetByName(const std::string& name);		// Returns a weak reference to an object by name

	private:

		// Helpers ========================

		static bool verifyInstantiation();	// Was this object instantiated?
		void loadCube();					// Load the cube mesh
		void loadTetrahedron();				// Load the tetrahedrion mesh
		void loadOctohedron();				// Load the octohedron mesh
		void loadPrism();					// Load the triangular prism mesh

		// Data ===========================

		static MeshRegistry* _instance;	// Internal singleton instance
		std::forward_list<std::shared_ptr<Mesh>> _resourceList;		// List of all the resource this registry can handle
		
	};

	
} // namespace sfew

#endif