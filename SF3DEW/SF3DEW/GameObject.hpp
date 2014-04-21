// GameObject
// Represents a single entity in the game that can update and draw
//
// Written by Jibran Syed (4-14-2014)

#ifndef SFEW_GAME_OBJECT_H
#define SFEW_GAME_OBJECT_H

#include <string>
//#include <forward_list>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>

#include "INameable.hpp"
#include "Transform.hpp"
#include "Component.hpp"
#include "AudioComponent.hpp"
#include "ObjectRendererComponent.hpp"
#include "FontRendererComponent.hpp"
#include "PhysicsComponent.hpp"
#include "CustomComponent.hpp"
#include "AllCustomComponentHeaders.hpp"

namespace stdext
{
	// Provides casting functions for weak_ptr
	template<class T, class U>
	std::weak_ptr<T> static_pointer_cast(std::weak_ptr<U> const & r)
	{
		return std::static_pointer_cast<T>(r.lock());
	}
	template<class T, class U>
	std::weak_ptr<T> dynamic_pointer_cast(std::weak_ptr<U> const & r)
	{
		return std::dynamic_pointer_cast<T>(r.lock());
	}
}

namespace sfew
{
	class GameObject : public INameable
	{
	public:

		// Ctor/Dtor ======================

		GameObject();
		~GameObject();

		// Routines =======================

		void Update();							// Updates the GameObject's states
		void Destroy();							// Marks the GameObject for deletion
		bool AddComponent(ComponentType type);	// Add a new component of the given type
		void OnCollision(PhysicsCollisionGroups otherGroup, 
						 std::weak_ptr<PhysicsEntity> otherEntity); // Message for when collision occurs

		// Properties =====================

		bool IsToBeDestroyed() const;
		std::weak_ptr<Transform> GetTransform() const;
		std::weak_ptr<Component> GetComponentByType(ComponentType type) const;
		std::weak_ptr<CustomComponent> GetCustomComponent(const std::string& name) const;
		bool HasPhysics() const;
		std::weak_ptr<PhysicsComponent> GetPhysicsComponent() const;

		// Templated Methods ==============

		template <typename T> std::weak_ptr<T> GetComponent() const;

	private:

		// Helpers ========================

		std::weak_ptr<GameObject> getSelf() const;

		// Data ===========================

		std::shared_ptr<GameObject> _self;		// A weak internal reference to this (using custom deleter)

		std::shared_ptr<Transform> _transform;									// The object's transform
		std::shared_ptr<AudioComponent> _audio;									// The object's audio
		std::shared_ptr<ObjectRendererComponent> _renderer;						// The object's 3D renderer
		std::shared_ptr<FontRendererComponent> _fontRenderer;					// The object's font renderer
		std::shared_ptr<PhysicsComponent> _physics;								// The object's physics properties
		//std::forward_list<std::shared_ptr<CustomComponent>> _customComponents;	// List of custom components

		// Hash table of custom components stored by type
		std::unordered_map<std::type_index, std::shared_ptr<CustomComponent>> _customComponents;

		// Flags ==========================

		bool _flaggedForDestruction;		// Should the GameObject get deleted? 

	};

	// Template Implementations ============================================
	template <typename T> std::weak_ptr<T> GameObject::GetComponent() const
	{
		// Get the Component's type
		std::type_index componentClass(typeid(T));

		if(std::type_index(typeid(*_audio)) == componentClass)
		{
			return std::static_pointer_cast<T>(_audio);
		}
		else
		{
			return std::static_pointer_cast<T>(std::shared_ptr<Component>());
		}
	}


} // namespace sfew

#endif