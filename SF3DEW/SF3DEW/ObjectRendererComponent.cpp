#include "ObjectRendererComponent.hpp"

#include <iostream>

#include "GameObject.hpp"
#include "MeshRegistry.hpp"
#include "MaterialRegistry.hpp"
#include "RendererContainer.hpp"

namespace sfew
{
	// Ctor/Dtor ========================================

	// Ctor
	ObjectRendererComponent::ObjectRendererComponent(std::weak_ptr<GameObject> owningGameObject) :
		Component(owningGameObject)
	{
		// Create the Object Renderer with defaults
		_renderer = std::shared_ptr<ObjectRenderer>(
			new ObjectRenderer(
				MeshRegistry::GetByName("CubeMesh"),
				MaterialRegistry::GetByName("Blank")
			)
		);

		// Make persistant, if owning GameObject is
		if(owningGameObject._Get()->IsPersistant())
		{
			_renderer->SetPersistance(true);
		}

		// Add it to the render container
		RendererContainer::Add(_renderer);

		// Run Start
		Start();
	}

	// Dtor
	ObjectRendererComponent::~ObjectRendererComponent()
	{
		
	}

	// Routines =========================================

	void ObjectRendererComponent::Start()
	{
		// Does nothing
	}

	void ObjectRendererComponent::Update()
	{
		std::weak_ptr<Transform> transform = GetGameObject()._Get()->GetTransform();
		Matrix4 modelMatrix = transform._Get()->GenerateModelMatrix();
		_renderer->UpdateModelMatrix(modelMatrix);
	}

	// Properties =========================================

	std::weak_ptr<ObjectRenderer> ObjectRendererComponent::GetRenderer() const
	{
		return _renderer;
	}

} // namespace sfew