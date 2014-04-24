// Font Renderer Component
// Component that allows the drawing of font-defined text
//
// Written by Jibran Syed (4-16-2014)

#ifndef SFEW_FONT_RENDERER_COMPONENT
#define SFEW_FONT_RENDERER_COMPONENT

#include <memory>

#include "Component.hpp"
#include "FontRenderer.hpp"

namespace sfew
{
	class FontRendererComponent : public Component
	{
	public:

		// Ctor/Dtor ======================

		FontRendererComponent(std::weak_ptr<GameObject> owningGameObject);
		virtual ~FontRendererComponent();

		// Routines =======================

		virtual void Start();
		virtual void Update();

		// Properties =====================

		std::weak_ptr<FontRenderer> GetRenderer() const;

	private:

		// Data ===========================
		
		std::shared_ptr<FontRenderer> _renderer;		// The font renderer itself

	};

	
} // namespace sfew

#endif