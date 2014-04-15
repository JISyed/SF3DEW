// Material Registry
// A registry for store all Material objects
//
// Written by Jibran Syed (4-14-2014)

#ifndef SFEW_MATERIAL_REGISTRY_H
#define SFEW_MATERIAL_REGISTRY_H

#include "Registry.hpp"
#include "Material.hpp"

namespace sfew
{
	class MaterialRegistry : public Registry
	{
	public:

		// Ctor/Dtor ======================

		MaterialRegistry();
		virtual ~MaterialRegistry();

		// Routines =======================

		virtual bool Load();						// Load all the resources
		virtual void Unload();						// Unload all the resources

		// Properties =====================

		static std::weak_ptr<Material> GetByName(const std::string& name);		// Returns a weak reference to an object by name

	private:

		// Helpers ========================

		static bool verifyInstantiation();	// Was this object instantiated?

		// Data ===========================

		static MaterialRegistry* _instance;	// Internal singleton instance
		std::forward_list<std::shared_ptr<Material>> _resourceList;		// List of all the resource this registry can handle
		
	};

	
} // namespace sfew

#endif