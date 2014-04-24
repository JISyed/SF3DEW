// FPS Text Prefabrication
// Example prefab that makes a HUD display showing FPS
//
// Written by Jibran Syed (4-22-2014)

// Required Headers
#ifndef SFEW_CUSTOM_PREFAB__FPS
#define SFEW_CUSTOM_PREFAB__FPS
#include "Prefabrication.hpp"

namespace sfew
{
	namespace prefab
	{
		class FpsPrefab : public Prefabrication
		{
		public:

			// Ctor/Dtor ======================

			FpsPrefab();
			virtual ~FpsPrefab();

			// Routines =======================

			virtual std::weak_ptr<GameObject> MakeObject();
			
		}; // End of custom prefab class header

	} // namespace sfew::prefab
} // namespace sfew

#endif