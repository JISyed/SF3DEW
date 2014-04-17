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
		Audio,
		ObjectRenderer,
		FontRenderer,
		Physics,
		Custom
	};

	class GameObject;

	class Component
	{
	public:

		// Ctor/Dtor ======================

		Component(std::weak_ptr<GameObject> owningGameObject);
		virtual ~Component();

		// Routines =======================

		

		// Properties =====================

		std::weak_ptr<GameObject> GetGameObject() const;
		//virtual ComponentType GetType() const = 0;

	private:

		// Helpers ========================

		

		// Data ===========================

		std::weak_ptr<GameObject> _gameObject;	// Back reference to GameObject
		
	};

	
} // namespace sfew

#endif