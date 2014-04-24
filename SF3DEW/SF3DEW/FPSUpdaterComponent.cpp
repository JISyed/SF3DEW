#include "FPSUpdaterComponent.hpp"
#include <iostream>
#include "GameObject.hpp"

// System Headers not needed in header
#include <string>

// SFEW Headers not needed in header
#include "Random.hpp"
#include "SystemTime.hpp"

namespace sfew
{
	namespace component
	{
		// Ctor/Dtor ========================================

		// Constructor
		FpsUpdaterCmpt::FpsUpdaterCmpt(std::weak_ptr<GameObject> owningGameObject) :
			CustomComponent(owningGameObject)
		{
			Start();
		}

		// Destructor
		FpsUpdaterCmpt::~FpsUpdaterCmpt()
		{
			Cleanup();
		}

		// Required Routines =========================================

		// Runs at contruction of component
		void FpsUpdaterCmpt::Start()
		{
			// Add a font render component and retrieve the font renderer
			GetGameObject()._Get()->AddComponent<FontRendererComponent>();
			auto fontRendererComponent = GetGameObject()._Get()->GetComponent<FontRendererComponent>();
			_fontRenderer = fontRendererComponent._Get()->GetRenderer();

			// Setup font rendering properties
			_fontRenderer._Get()->SetFontSize(48);
			_fontRenderer._Get()->SetColor(0.0f, 0.5f, 0.7f, 1.0f);
			_fontRenderer._Get()->SetPosition(10, 10);
		}

		// Runs every frame
		void FpsUpdaterCmpt::Update()
		{
			// Get current FPS and update font renderer string
			float currFPS = SystemTime::GetFPS();
			_fpsStringWriter.str(std::string());
			_fpsStringWriter << "FPS: " << currFPS;
			_fontRenderer._Get()->SetTextString(_fpsStringWriter.str());
		}

		// Runs at destruction of component
		void FpsUpdaterCmpt::Cleanup()
		{

		}

		// Run if there is a collision with an object of a different group
		void FpsUpdaterCmpt::OnCollision(PhysicsCollisionGroups otherGroup, 
										 std::weak_ptr<PhysicsEntity> otherEntity)
		{
			// Does nothing here
		}

	} // namespace sfew::component
} // namespace sfew