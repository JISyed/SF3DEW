// Container
// Class that holds weak references to a bunch of objects to update them
//
// Written by Jibran Syed (4-18-2014)

#ifndef SFEW_CONTAINER_H
#define SFEW_CONTAINER_H

#include <memory>
#include <forward_list>

#include "ISystemObject.hpp"

namespace sfew
{
	class Container : public ISystemObject
	{
	public:

		// Ctor/Dtor ======================

		Container();
		virtual ~Container();

		// Routines =======================

		virtual bool Setup() = 0;
		virtual bool Update() = 0;
		virtual bool Cleanup() = 0;

	};

	
} // namespace sfew

#endif