// Demo Scene
// Example Scene demonstriating SF3DEW
//
// Written by Jibran Syed (4-23-2014)

// Required Headers
#ifndef SFEW_CUSTOM_SCENE__DEMO
#define SFEW_CUSTOM_SCENE__DEMO
#include "Scene.hpp"

namespace sfew
{
	namespace scene
	{
		class DemoScene : public Scene
		{
		public:

			// Ctor/Dtor ======================

			DemoScene();
			virtual ~DemoScene();

			// Routines =======================

			virtual bool Load();			// Clears current scene and loads
			virtual bool LoadAdditive();	// Loads without clearing current scene
			
		};

	} // namespace sfew::scene
} // namespace sfew

#endif