// GameObject
// Represents a single entity in the game that can update and draw
//
// Written by Jibran Syed (4-14-2014)

#ifndef SFEW_GAME_OBJECT_H
#define SFEW_GAME_OBJECT_H

// SYSTEM HEADERS HERE

#include "INameable.hpp"
#include "Component.hpp"

namespace sfew
{
	class GameObject : public INameable
	{
	public:

		// Ctor/Dtor ======================

		GameObject();
		~GameObject();

		// Routines =======================

		

		// Properties =====================

	private:

		// Helpers ========================

		

		// Data ===========================

		
		
	};

	
} // namespace sfew

#endif