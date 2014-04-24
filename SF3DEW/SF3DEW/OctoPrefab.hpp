// Octohedron Prefabrication
// Example Prefab that makes an orange textured octohedron
//
// Written by Jibran Syed (4-22-2014)

// Required Headers
#ifndef SFEW_CUSTOM_PREFAB__OCTO
#define SFEW_CUSTOM_PREFAB__OCTO
#include "Prefabrication.hpp"

namespace sfew
{
	namespace prefab
	{
		class OctoPrefab : public Prefabrication
		{
		public:

			// Ctor/Dtor ======================

			OctoPrefab();
			virtual ~OctoPrefab();

			// Routines =======================

			virtual std::weak_ptr<GameObject> MakeObject();
			
		}; // End of custom prefab class header

	} // namespace sfew::prefab
} // namespace sfew

#endif