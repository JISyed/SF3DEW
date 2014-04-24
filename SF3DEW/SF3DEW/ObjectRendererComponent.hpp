// Object Renderer Component
// Component that allows the drawing of a 3D object
//
// Written by Jibran Syed (4-16-2014)

#ifndef SFEW_OBJECT_RENDERER_COMPONENT
#define SFEW_OBJECT_RENDERER_COMPONENT

#include <memory>
#include "Component.hpp"
#include "ObjectRenderer.hpp"

namespace sfew
{
	class ObjectRendererComponent : public Component
	{
	public:

		// Ctor/Dtor ======================

		ObjectRendererComponent(std::weak_ptr<GameObject> owningGameObject);
		virtual ~ObjectRendererComponent();

		// Routines =======================

		virtual void Start();
		virtual void Update();

		// Properties =====================

		std::weak_ptr<ObjectRenderer> GetRenderer() const;

	private:

		// Data ===========================
		
		std::shared_ptr<ObjectRenderer> _renderer;		// The renderer itself

	};

	
} // namespace sfew

#endif