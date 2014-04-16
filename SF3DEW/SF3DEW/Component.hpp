// Component
// Modular method of giving GameObjects properties
//
// Written by Jibran Syed (4-14-2014)

#ifndef SFEW_COMPONENT_H
#define SFEW_COMPONENT_H

#include <memory>

namespace sfew
{
	// Enum for component types
	enum class ComponentType
	{
		Invalid,
		Audio,
		ObjectRenderer,
		FontRenderer,
		Physics,
		Custom
	};

	class Component
	{
	public:

		// Ctor/Dtor ======================

		Component();
		~Component();

		// Routines =======================

		

		// Properties =====================

	protected:

		// Inhertiable Data ===============

		ComponentType _componentType;			// What type of component is this?
		class GameObject;
		std::weak_ptr<GameObject> _gameObject;	// Back reference to GameObject

	private:

		// Helpers ========================

		

		// Data ===========================

		
		
	};

	
} // namespace sfew

#endif