// Font Renderer Component
// Component that allows the drawing of font-defined text
//
// Written by Jibran Syed (4-16-2014)

#ifndef SFEW_FONT_RENDERER_COMPONENT
#define SFEW_FONT_RENDERER_COMPONENT

#include <memory>

#include "Component.hpp"

namespace sfew
{
	class FontRendererComponent : public Component
	{
	public:

		// Ctor/Dtor ======================

		FontRendererComponent(std::weak_ptr<GameObject> owningGameObject);
		virtual ~FontRendererComponent();

		// Routines =======================

		

		// Properties =====================

		virtual ComponentType GetType() const;

	private:

		// Helpers ========================

		

		// Data ===========================
		
	};

	
} // namespace sfew

#endif