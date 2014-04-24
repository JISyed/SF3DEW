#include "GameObject.hpp"

#include <iostream>

#include "GameObjectContainer.hpp"

namespace sfew
{
	// Custom shared_ptr deleter that does nothing =====
	struct shared_un_deleter
	{
		void operator()(void const*) const{}
	};

	// Static Data ======================================

	std::type_index GameObject::_audioComponentType = 
		std::type_index( typeid(AudioComponent) );
	std::type_index GameObject::_physicsComponentType = 
		std::type_index( typeid(PhysicsComponent) );
	std::type_index GameObject::_rendererComponentType = 
		std::type_index( typeid(ObjectRendererComponent) );
	std::type_index GameObject::_fontRendererComponentType = 
		std::type_index( typeid(FontRendererComponent) );

	// Ctor/Dtor ========================================

	// Ctor
	GameObject::GameObject() : 
		INameable("Unnamed GameObject"),
		_flaggedForDestruction(false),
		_isPersistant(false)
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
		if(!_customComponents.empty())
		{
			for(auto& cmpt : _customComponents)
			{
				cmpt.second->Update();
			}
		}

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

	// Message for when collision occurs
	void GameObject::OnCollision(PhysicsCollisionGroups otherGroup, 
								 std::weak_ptr<PhysicsEntity> otherEntity)
	{
		// Message all custom components if they exist
		if(!_customComponents.empty())
		{
			for(auto& cmpt : _customComponents)
			{
				cmpt.second->OnCollision(otherGroup, otherEntity);
			}
		}
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

	void GameObject::SetPersistance(bool willBePersistant)
	{
		// Set GameObject's persistance
		_isPersistant = willBePersistant;

		// Set PhysicsEntity's persistance, if exists
		if(_physics)
		{
			_physics->GetPhysicsEntity()._Get()->SetPersistance(willBePersistant);
		}

		// Set ObjectRenderer's persistance, if exists
		if(_renderer)
		{
			_renderer->GetRenderer()._Get()->SetPersistance(willBePersistant);
		}

		// Set FontRenderer's persistance, if exists
		if(_fontRenderer)
		{
			_fontRenderer->GetRenderer()._Get()->SetPersistance(willBePersistant);
		}
	}

	bool GameObject::IsPersistant() const
	{
		return _isPersistant;
	}

	// Helpers =========================================

	std::weak_ptr<GameObject> GameObject::getSelf() const
	{
		return _self;
	}

} // namespace sfew