// Shader Registry
// A registry for store all Shader objects
//
// Written by Jibran Syed (4-14-2014)

#ifndef SFEW_SHADER_REGISTRY_H
#define SFEW_SHADER_REGISTRY_H

#include "Registry.hpp"
#include "Shader.hpp"
#include "Camera.hpp"

class MeshRegistry;

namespace sfew
{
	class ShaderRegistry : public Registry
	{
	public:

		// Ctor/Dtor ======================

		ShaderRegistry();
		virtual ~ShaderRegistry();

		// Routines =======================

		virtual bool Load();				// Load all the resources
		virtual void Unload();				// Unload all the resources
		void UpdateCameraDataInShaders();	// Sends down view and projection matrix if changed

		// Properties =====================

		static std::weak_ptr<Shader> GetByName(const std::string& name);		// Returns a weak reference to an object by name

	private:

		// Helpers ========================

		static bool verifyInstantiation();	// Was this object instantiated?

		// Data ===========================

		friend class MeshRegistry;			// MeshRegistry needs to loop through the shader resource list
		static ShaderRegistry* _instance;	// Internal singleton instance
		std::forward_list<std::shared_ptr<Shader>> _resourceList;		// List of all the resource this registry can handle
		
	};

	
} // namespace sfew

#endif