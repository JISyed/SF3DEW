// GameObject
// Represents a single entity in the game that can update and draw
//
// Written by Jibran Syed (4-14-2014)

#ifndef SFEW_GAME_OBJECT_H
#define SFEW_GAME_OBJECT_H

#include <string>
#include <forward_list>

#include "INameable.hpp"
#include "Transform.hpp"
#include "Component.hpp"
#include "AudioComponent.hpp"
#include "ObjectRendererComponent.hpp"
#include "FontRendererComponent.hpp"
#include "PhysicsComponent.hpp"
#include "CustomComponent.hpp"

namespace sfew
{
	class GameObject : public INameable
	{
	public:

		// Ctor/Dtor ======================

		GameObject();
		~GameObject();

		// Routines =======================

		bool AddComponent(ComponentType type);	// Add a new component of the given type
		void Destroy();							// Marks the GameObject for deletion

		// Properties =====================

		bool IsToBeDestroyed();
		std::weak_ptr<Transform> GetTransform() const;
		std::weak_ptr<Component> GetComponent(ComponentType type) const;
		std::weak_ptr<CustomComponent> GetCustomComponent(const std::string& name) const;

	private:

		// Helpers ========================

		

		// Data ===========================

		//std::weak_ptr<GameObject> _self;										// Weak reference to itself
		std::shared_ptr<Transform> _transform;									// The object's transform
		std::shared_ptr<AudioComponent> _audio;									// The object's audio
		std::shared_ptr<ObjectRendererComponent> _renderer;						// The object's 3D renderer
		std::shared_ptr<FontRendererComponent> _fontRenderer;					// The object's font renderer
		std::shared_ptr<PhysicsComponent> _physics;								// The object's physics properties
		std::forward_list<std::shared_ptr<CustomComponent>> _customComponents;	// List of custom components

		// Flags ==========================

		bool _flaggedForDestruction;		// Should the GameObject get deleted? 

	};

	
} // namespace sfew

#endif