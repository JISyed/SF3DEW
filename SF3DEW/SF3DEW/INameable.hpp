// Nameable Interface (INameable)
// Protocol that gives objects a string name
//
// Written by Jibran Syed (4-6-2014)

#ifndef INAMEABLE_H
#define INAMEABLE_H

#include <string>

namespace sfew
{
	
	class INameable
	{
	public:

		// Ctor/Dtor ======================
	
		INameable() : _name("") {}
		INameable(const std::string& newName) : _name(newName) {}
		virtual ~INameable() {}

		// Properties =====================

		const std::string& GetName() const {return _name;}
		void SetName(const std::string& newName) { _name = newName; }

	protected:

		// Data ===========================

		std::string _name;	// Name of the object

	};

} // namespace sfew

#endif