// Interface for System Objects (ISystemObject)
// Protocol defining mandatory methods every system object has
//
// Written by Jibran Syed (4-12-2014)

#ifndef ISYSTEMOBJECT_H
#define ISYSTEMOBJECT_H

namespace sfew
{
	
	class ISystemObject
	{
	public:

		// System Routines ================

		virtual bool Setup() = 0;		// Run at the begining of the program
		virtual bool Update() = 0;		// Run every loop
		virtual bool Cleanup() = 0;		// Run at the end of the program
	};

} // namespace sfew

#endif