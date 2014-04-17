// Object Renderer Component
// Component that allows the drawing of a 3D object
//
// Written by Jibran Syed (4-16-2014)

#ifndef SFEW_OBJECT_RENDERER_COMPONENT
#define SFEW_OBJECT_RENDERER_COMPONENT

#include <memory>
#include "Component.hpp"

namespace sfew
{
	class ObjectRendererComponent : public Component
	{
	public:

		// Ctor/Dtor ======================

		ObjectRendererComponent(std::weak_ptr<GameObject> owningGameObject);
		virtual ~ObjectRendererComponent();

		// Routines =======================

		

		// Properties =====================

		virtual ComponentType GetType() const;

	private:

		// Helpers ========================

		

		// Data ===========================
		
	};

	
} // namespace sfew

#endif