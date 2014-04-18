#include "FontRendererComponent.hpp"

#include <iostream>

#include "GameObject.hpp"
#include "FontRegistry.hpp"

namespace sfew
{
	// Ctor/Dtor ========================================

	FontRendererComponent::FontRendererComponent(std::weak_ptr<GameObject> owningGameObject) :
		Component(owningGameObject)
	{
		// Make the font renderer with defaults
		_renderer = std::shared_ptr<FontRenderer>(
			new FontRenderer(
				FontRegistry::GetByName("Mars")._Get()->GetReference()
			)
		);

		// Run Start
		Start();
	}

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

	ComponentType FontRendererComponent::GetType() const
	{
		return ComponentType::FontRenderer;
	}

	std::weak_ptr<FontRenderer> FontRendererComponent::GetRenderer() const
	{
		return _renderer;
	}

	// Helpers =========================================

} // namespace sfew