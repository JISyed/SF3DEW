#include "CustomComponent.hpp"

#include <iostream>

#include "GameObject.hpp"

namespace sfew
{
	// Ctor/Dtor ========================================

	CustomComponent::CustomComponent(std::weak_ptr<GameObject> owningGameObject) :
		Component(owningGameObject)
	{
		
	}

	CustomComponent::~CustomComponent()
	{
		
	}

	// Routines =========================================
	/*
	void CustomComponent::Start()
	{

	}

	void CustomComponent::Update()
	{

	}

	void CustomComponent::Cleanup()
	{

	}

	void CustomComponent::OnCollision(PhysicsCollisionGroups otherGroup, 
									  std::weak_ptr<PhysicsEntity> otherEntity)
	{

	}
	*/
	// Properties =========================================


	// Helpers =========================================

} // namespace sfew