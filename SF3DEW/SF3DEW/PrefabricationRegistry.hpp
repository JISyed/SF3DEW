// Prefabrication Registry
// A registry for store all Prefabrication objects
//
// Written by Jibran Syed (4-14-2014)

#ifndef SFEW_PREFABRICATION_REGISTRY_H
#define SFEW_PREFABRICATION_REGISTRY_H

#include "Registry.hpp"
//#include "Prefabrication.hpp"

namespace sfew
{
	class PrefabricationRegistry : public Registry
	{
	public:

		// Ctor/Dtor ======================

		PrefabricationRegistry();
		virtual ~PrefabricationRegistry();

		// Routines =======================

		virtual bool Load();						// Load all the resources
		virtual void Unload();						// Unload all the resources

		// Properties =====================

		//static std::weak_ptr<Prefabrication> GetByName();		// Returns a weak reference to an object by name

	private:

		// Helpers ========================

		static bool verifyInstantiation();	// Was this object instantiated?

		// Data ===========================

		static PrefabricationRegistry* _instance;	// Internal singleton instance
		//std::forward_list<std::shared_ptr<Prefabrication>> _resourceList;		// List of all the resource this registry can handle
		
	};

	
} // namespace sfew

#endif