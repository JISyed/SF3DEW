// Cube Prefabrication
// Example that makes a cube with patch texture
//
// Written by Jibran Syed (4-22-2014)

// Required Headers
#ifndef SFEW_CUSTOM_PREFAB__CUBE
#define SFEW_CUSTOM_PREFAB__CUBE
#include "Prefabrication.hpp"

namespace sfew
{
	namespace prefab
	{
		class CubePrefab : public Prefabrication
		{
		public:

			// Ctor/Dtor ======================

			CubePrefab();
			virtual ~CubePrefab();

			// Routines =======================

			virtual std::weak_ptr<GameObject> MakeObject();
			
		}; // End of custom prefab class header

	} // namespace sfew::prefab
} // namespace sfew

#endif