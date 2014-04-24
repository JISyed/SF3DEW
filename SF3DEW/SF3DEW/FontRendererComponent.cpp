#include "FontRendererComponent.hpp"

#include <iostream>

#include "GameObject.hpp"
#include "FontRegistry.hpp"
#include "RendererContainer.hpp"

namespace sfew
{
	// Ctor/Dtor ========================================

	// Ctor
	FontRendererComponent::FontRendererComponent(std::weak_ptr<GameObject> owningGameObject) :
		Component(owningGameObject)
	{
		// Make the font renderer with defaults
		_renderer = std::shared_ptr<FontRenderer>(
			new FontRenderer(
				FontRegistry::GetByName("Mars")._Get()->GetReference()
			)
		);

		// Make persistant, if owning GameObject is
		if(owningGameObject._Get()->IsPersistant())
		{
			_renderer->SetPersistance(true);
		}

		// Add it to the renderer container
		RendererContainer::Add(_renderer);

		// Run Start
		Start();
	}

	// Dtor
	FontRendererComponent::~FontRendererComponent()
	{
		
	}

	// Routines =========================================

	void FontRendererComponent::Start()
	{
		_renderer->SetTextString("Example Text");
	}

	void FontRendererComponent::Update()
	{
		// Does nothing
	}

	// Properties =========================================

	std::weak_ptr<FontRenderer> FontRendererComponent::GetRenderer() const
	{
		return _renderer;
	}

} // namespace sfew