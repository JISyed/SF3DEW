// Font Registry
// A registry for store all SFML Font objects
//
// Written by Jibran Syed (4-14-2014)

#ifndef SFEW_FONT_REGISTRY_H
#define SFEW_FONT_REGISTRY_H

#include <SFML/Graphics/Font.hpp>

#include "Registry.hpp"

namespace sfew
{
	class FontRegistry : public Registry
	{
	public:

		// Ctor/Dtor ======================

		FontRegistry();
		virtual ~FontRegistry();

		// Routines =======================

		virtual bool Load();						// Load all the resources
		virtual void Unload();						// Unload all the resources

		// Properties =====================

		static std::weak_ptr<sf::Font> GetByName(const std::string& name);		// Returns a weak reference to an object by name

	private:

		// Helpers ========================

		static bool verifyInstantiation();	// Was this object instantiated?

		// Data ===========================

		static FontRegistry* _instance;	// Internal singleton instance
		std::forward_list<std::shared_ptr<sf::Font>> _resourceList;		// List of all the resource this registry can handle
		
	};

	
} // namespace sfew

#endif