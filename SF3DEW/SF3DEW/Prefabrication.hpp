// Prefabrication
// Prototype definitions for assembling pre-made GameObjects
//
// Written by Jibran Syed (4-15-2014)

#ifndef SFEW_PREFABRICATION_H
#define SFEW_PREFABRICATION_H

#include <SFML/System/NonCopyable.hpp>

#include "INameable.hpp"

namespace sfew
{
	class Prefabrication : sf::NonCopyable, public INameable
	{
	public:

		// Ctor/Dtor ======================

		Prefabrication();
		~Prefabrication();

		// Routines =======================

		

		// Properties =====================

	private:

		// Helpers ========================

		

		// Data ===========================

		
		
	};

	
} // namespace sfew

#endif