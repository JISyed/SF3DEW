// GameObject
// Represents a single entity in the game that can update and draw
//
// Written by Jibran Syed (4-14-2014)

#ifndef SFEW_GAME_OBJECT_H
#define SFEW_GAME_OBJECT_H

#include <string>
#include <unordered_map>
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

		// Templated Methods ==============

		template <typename T> std::weak_ptr<T> GetComponent() const;
		template <typename T> bool AddCustomComponent();
		template <typename T> std::weak_ptr<T> GetCustomComponent() const;

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

		// Hash table of custom components stored by type
		std::unordered_map<std::type_index, std::shared_ptr<CustomComponent>> _customComponents;

		// Type IDs =======================

		static std::type_index _audioComponentType;
		static std::type_index _physicsComponentType;
		static std::type_index _rendererComponentType;
		static std::type_index _fontRendererComponentType;

		// Flags ==========================

		bool _flaggedForDestruction;		// Should the GameObject get deleted? 

	};

	// Template Implementations ============================================

	// Get component based on the component type
	template <typename T> std::weak_ptr<T> GameObject::GetComponent() const
	{
		// Get the Component's type
		std::type_index componentClass(typeid(T));

		// Add component if matches in type given
		if(GameObject::_audioComponentType == componentClass)
		{
			return std::dynamic_pointer_cast<T>(_audio);
		}
		else if(GameObject::_physicsComponentType == componentClass)
		{
			return std::dynamic_pointer_cast<T>(_physics);
		}
		else if(GameObject::_rendererComponentType == componentClass)
		{
			return std::dynamic_pointer_cast<T>(_renderer);
		}
		else if(GameObject::_fontRendererComponentType == componentClass)
		{
			return std::dynamic_pointer_cast<T>(_fontRenderer);
		}
		else
		{
			std::cout << "Warning: Could not find component of type \"" << 
				componentClass.name() << "\"." << std::endl;
			std::cout << "Check for NULL before doing anything.\n";
			return std::dynamic_pointer_cast<T>(std::shared_ptr<Component>());
		}
	}

	// Add a custom component using template parameter
	template <typename T> bool GameObject::AddCustomComponent()
	{
		std::type_index newComponentType(typeid(T));

		// Check if custom component was already added
		if(_customComponents.count(newComponentType) != 0)
		{
			std::cout << "Component \"" << newComponentType.name() <<
				"\" already added!" << std::endl;
			return false;
		}

		// Make new component of type
		std::shared_ptr<T> newComponent(new T(getSelf()));

		// Add it to hash table
		_customComponents[std::type_index(typeid(*newComponent))] = newComponent;

		return true;
	}

	// Get a custom component using template parameter
	// Thanks to vijoc (http://gamedev.stackexchange.com/a/57282)
	template <typename T> std::weak_ptr<T> GameObject::GetCustomComponent() const
	{
		std::type_index index(typeid(T));

		// Return a weak pointer to the queried custom component if found
		if(_customComponents.count(std::type_index(typeid(T))) != 0)
		{
			return std::static_pointer_cast<T>(_customComponents.at(index));
		}

		// If you're here, no component was found
		return std::static_pointer_cast<T>(std::shared_ptr<CustomComponent>());
	}

} // namespace sfew

#endif