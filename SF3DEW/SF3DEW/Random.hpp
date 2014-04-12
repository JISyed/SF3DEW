// Random
// Aids in randomly generating numbers
// Not intended for psudorandom, *tries* to approach true random
//
// Written by Jibran Syed (4-12-2014)

#ifndef SFEW_RANDOM_H
#define SFEW_RANDOM_H

namespace sfew
{
	class Random
	{
	public:

		// Static Routines ================

		static float NormalizedFloat();		// Get a number between 0 and 1
		static float Range(float min, float max);	// Get a float between the range inclusively
		static int Range(int min, int max);	// Get an int between the range inclusively

	private:

		// Static Helpers =================

		static void updateTimeStamp();		// Updates the time stamp to the current time
		static unsigned long newSeed();		// Randomly generate a seed from the timestamp

		// Static Data ====================

		static unsigned long _timeStamp;	// Represent the current time
		
	};

	
} // namespace sfew

#endif