// Registry
// Stores a list of resources to load before the game starts
//
// Written by Jibran Syed (MONTH-DAY-YEAR)

#ifndef SFEW_REGISTRY_H
#define SFEW_REGISTRY_H

#include <memory>
#include <string>
#include <forward_list>
#include <SFML/System/NonCopyable.hpp>

namespace sfew
{
	class Registry : sf::NonCopyable
	{
	public:

		// Ctor/Dtor ======================

		Registry();
		virtual ~Registry();

		// Routines =======================

		virtual bool Load() = 0;		// Load all the resources
		virtual void Unload() = 0;		// Unload all the resources
		
	protected:

		// Inhertiable Data ===============

		bool _resourcesLoaded;
	};

	
} // namespace sfew

#endif