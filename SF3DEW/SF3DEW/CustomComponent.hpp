// Custom Component
// Base class for all custom made component scripts
// Similar in concept to Unity's MonoBehavior
//
// Written by Jibran Syed (4-16-2014)

#ifndef SFEW_CUSTOM_COMPONENT
#define SFEW_CUSTOM_COMPONENT

#include "INameable.hpp"
#include "Component.hpp"

namespace sfew
{
	class CustomComponent : public Component, public INameable
	{
	public:

		// Ctor/Dtor ======================

		CustomComponent(std::weak_ptr<GameObject> owningGameObject);
		virtual ~CustomComponent();

		// Routines =======================

		virtual void Start() = 0;
		virtual void Update() = 0;

		// Properties =====================

		virtual ComponentType GetType() const;

	private:

		// Helpers ========================

		

		// Data ===========================


		
	};

	
} // namespace sfew

#endif