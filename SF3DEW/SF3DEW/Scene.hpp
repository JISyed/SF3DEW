// Scene
// Represents levels which load GameObjects and Prefabrications
//
// Written by Jibran Syed (4-15-2014)

#ifndef SFEW_SCENE_H
#define SFEW_SCENE_H

#include <SFML/System/NonCopyable.hpp>

#include "INameable.hpp"

namespace sfew
{
	class Scene : sf::NonCopyable, public INameable
	{
	public:

		// Ctor/Dtor ======================

		Scene();
		~Scene();

		// Routines =======================

		

		// Properties =====================

	private:

		// Helpers ========================

		

		// Data ===========================

		
		
	};

	
} // namespace sfew

#endif