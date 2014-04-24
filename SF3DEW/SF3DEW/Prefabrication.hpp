// Prefabrication
// Prototype definitions for assembling pre-made GameObjects
//
// Written by Jibran Syed (4-15-2014)

#ifndef SFEW_PREFABRICATION_H
#define SFEW_PREFABRICATION_H

#include <SFML/System/NonCopyable.hpp>
#include <memory>

#include "GameObject.hpp"

namespace sfew
{
	class Prefabrication : sf::NonCopyable
	{
	public:

		// Ctor/Dtor ======================

		Prefabrication();
		virtual ~Prefabrication();

		// Routines =======================

		virtual std::weak_ptr<GameObject> MakeObject() = 0;
		
	};

	
} // namespace sfew

#endif