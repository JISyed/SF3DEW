// Component
// Modular method of giving GameObjects properties
//
// Written by Jibran Syed (4-14-2014)

#ifndef SFEW_COMPONENT_H
#define SFEW_COMPONENT_H

#include <memory>

namespace sfew
{
	class GameObject;

	class Component
	{
	public:

		// Ctor/Dtor ======================

		Component(std::weak_ptr<GameObject> owningGameObject);
		virtual ~Component();

		// Routines =======================

		virtual void Start() = 0;
		virtual void Update() = 0;

		// Properties =====================

		std::weak_ptr<GameObject> GetGameObject() const;

	private:

		// Data ===========================

		std::weak_ptr<GameObject> _gameObject;	// Back reference to GameObject
		
	};

	
} // namespace sfew

#endif