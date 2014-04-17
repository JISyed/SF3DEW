#include "GameObject.hpp"

#include <iostream>

namespace sfew
{
	// Ctor/Dtor ========================================

	// Ctor
	GameObject::GameObject() : 
		INameable("Unnamed GameObject"),
		//_self(this),
		_flaggedForDestruction(false)
	{
		
	}

	// Dtor
	GameObject::~GameObject()
	{
		
	}

	// Routines =========================================

	// Properties =========================================

	// Helpers =========================================

} // namespace sfew