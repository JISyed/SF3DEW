// Scene
// Represents levels which load GameObjects and Prefabrications
//
// Written by Jibran Syed (4-15-2014)

#ifndef SFEW_SCENE_H
#define SFEW_SCENE_H

#include <memory>
#include <SFML/System/NonCopyable.hpp>

namespace sfew
{
	class Scene : sf::NonCopyable
	{
	public:

		// Ctor/Dtor ======================

		Scene();
		virtual ~Scene();

		// Routines =======================

		virtual bool Load() = 0;
		virtual bool LoadAdditive() = 0;
		
	};

	
} // namespace sfew

#endif