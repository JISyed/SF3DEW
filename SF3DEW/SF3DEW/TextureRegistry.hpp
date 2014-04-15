// Texture Registry
// A registry for store all Texture objects
//
// Written by Jibran Syed (4-14-2014)

#ifndef SFEW_TEXTURE_REGISTRY_H
#define SFEW_TEXTURE_REGISTRY_H

#include "Registry.hpp"
#include "Texture.hpp"

namespace sfew
{
	class TextureRegistry : public Registry
	{
	public:

		// Ctor/Dtor ======================

		TextureRegistry();
		virtual ~TextureRegistry();

		// Routines =======================

		virtual bool Load();						// Load all the resources
		virtual void Unload();						// Unload all the resources

		// Properties =====================

		static std::weak_ptr<Texture> GetByName(const std::string& name);		// Returns a weak reference to an object by name

	private:

		// Helpers ========================

		static bool verifyInstantiation();	// Was this object instantiated?

		// Data ===========================

		static TextureRegistry* _instance;	// Internal singleton instance
		std::forward_list<std::shared_ptr<Texture>> _resourceList;		// List of all the resource this registry can handle
		
	};

	
} // namespace sfew

#endif