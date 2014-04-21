#include "GameObject.hpp"

#include <iostream>
#include <type_traits>

#include "GameObjectContainer.hpp"

namespace sfew
{
	// Custom shared_ptr deleter that does nothing =====
	struct shared_un_deleter
	{
		void operator()(void const*) const{}
	};

	// Ctor/Dtor ========================================

	// Ctor
	GameObject::GameObject() : 
		INameable("Unnamed GameObject"),
		_flaggedForDestruction(false)
	{
		// Prevent ownership of this object by the shared pointer
		_self = std::shared_ptr<GameObject>(this, shared_un_deleter() );

		// Create the transform
		_transform = std::shared_ptr<Transform>(new Transform());
	}

	// Dtor
	GameObject::~GameObject()
	{
		if(!_customComponents.empty())
		{
			_customComponents.clear();
		}
	}

	// Routines =========================================

	// Updates the GameObject's states
	void GameObject::Update()
	{
		// Update all custom components if they exist


		// Update the builtin components if they exist
		//if(_audio) _audio->Update(); // Does nothing
		if(_physics) _physics->Update();
		if(_renderer) _renderer->Update();
		//if(_fontRenderer) _fontRenderer->Update(); // Does nothing
	}

	// Marks the GameObject for deletion
	void GameObject::Destroy()
	{
		_flaggedForDestruction = true;
	}

	// Add a new component of the given type
	bool GameObject::AddComponent(ComponentType type)
	{
		// Check if the component type was already added
		switch (type)
		{
		case ComponentType::Audio:
			if(_audio) return false;
			break;
		case ComponentType::ObjectRenderer:
			if(_renderer) return false;
			break;
		case ComponentType::FontRenderer:
			if(_fontRenderer) return false;
			break;
		case ComponentType::Physics:
			if(_physics) return false;
			break;
		case ComponentType::Custom:
			// Cannot add custom components with this method
			return false;
			break;
		}

		// Add the specified component
		switch (type)
		{
		case ComponentType::Audio:
			_audio = std::shared_ptr<AudioComponent>(new AudioComponent(getSelf()));
			break;
		case ComponentType::ObjectRenderer:
			_renderer = std::shared_ptr<ObjectRendererComponent>(new ObjectRendererComponent(getSelf()));
			break;
		case ComponentType::FontRenderer:
			_fontRenderer = std::shared_ptr<FontRendererComponent>(new FontRendererComponent(getSelf()));
			break;
		case ComponentType::Physics:
			_physics = std::shared_ptr<PhysicsComponent>(new PhysicsComponent(getSelf()));
			break;
		}

		// Success
		return true;
	}

	// Message for when collision occurs
	void GameObject::OnCollision(PhysicsCollisionGroups otherGroup, 
								 std::weak_ptr<PhysicsEntity> otherEntity)
	{
		// STILL NEEDS TO BE IMPLEMENTED!
	}

	// Properties =========================================

	bool GameObject::IsToBeDestroyed() const
	{
		return _flaggedForDestruction;
	}

	std::weak_ptr<Transform> GameObject::GetTransform() const
	{
		return _transform;
	}

	std::weak_ptr<Component> GameObject::GetComponentByType(ComponentType type) const
	{
		switch (type)
		{
		case ComponentType::Audio:
			return _audio;
			break;
		case ComponentType::ObjectRenderer:
			return _renderer;
			break;
		case ComponentType::FontRenderer:
			return _fontRenderer;
			break;
		case ComponentType::Physics:
			return _physics;
			break;
		case ComponentType::Custom:
			// Cannot retrieve a custom component with this method
			return std::weak_ptr<CustomComponent>();
			break;
		}

		// To stop warning C4715
		return std::weak_ptr<Component>();
	}

	bool GameObject::HasPhysics() const
	{
		if(_physics) return true;

		return false;
	}

	std::weak_ptr<PhysicsComponent> GameObject::GetPhysicsComponent() const
	{
		return _physics;
	}

	// Helpers =========================================

	std::weak_ptr<GameObject> GameObject::getSelf() const
	{
		return _self;
	}

} // namespace sfew