// Scene Registry
// A registry for store all Scene objects
//
// Written by Jibran Syed (4-14-2014)

#ifndef SFEW_SCENE_REGISTRY_H
#define SFEW_SCENE_REGISTRY_H

#include "Registry.hpp"
//#include "Scene.hpp"

namespace sfew
{
	class SceneRegistry : public Registry
	{
	public:

		// Ctor/Dtor ======================

		SceneRegistry();
		virtual ~SceneRegistry();

		// Routines =======================

		virtual bool Load();						// Load all the resources
		virtual void Unload();						// Unload all the resources

		// Properties =====================

		//static std::weak_ptr<Scene> GetByName(const std::string& name);		// Returns a weak reference to an object by name

	private:

		// Helpers ========================

		static bool verifyInstantiation();	// Was this object instantiated?

		// Data ===========================

		static SceneRegistry* _instance;	// Internal singleton instance
		//std::forward_list<std::shared_ptr<Scene>> _resourceList;		// List of all the resource this registry can handle
		
	};

	
} // namespace sfew

#endif