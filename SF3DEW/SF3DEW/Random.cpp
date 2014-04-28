#include "Random.hpp"

#include <random>
#include <chrono>

namespace sfew
{
	// Static Data ========================================

	unsigned long Random::_timeStamp = 0;

	// Static Routines =========================================

	// Get a number between 0 and 1
	float Random::NormalizedFloat()
	{
		// Create random generator engine
		std::mt19937 generator(Random::newSeed());

		// Create a uniform distrubutor between the desired range
		std::uniform_real_distribution<float> distributor(0.0f, 1.0f);

		// Generate a random number
		return distributor(generator);
	}

	// Get a float between the range inclusively
	float Random::Range(float min, float max)
	{
		// Create random generator engine
		std::mt19937 generator(Random::newSeed());

		// Create a uniform distrubutor between the desired range
		std::uniform_real_distribution<float> distributor(min, max);

		// Generate a random number
		return distributor(generator);
	}

	// Get an int between the range inclusively
	int Random::Range(int min, int max)
	{
		// Create random generator engine
		std::mt19937 generator(Random::newSeed());

		// Create a uniform distrubutor between the desired range
		std::uniform_int_distribution<int> distributor(min, max);

		// Generate a random number
		return distributor(generator);
	}

	// Static Helpers =========================================

	// Updates the time stamp to the current time
	void Random::updateTimeStamp()
	{
		Random::_timeStamp = (unsigned long) std::chrono::steady_clock::now()
														.time_since_epoch()
														.count();
	}

	// Randomly generate a seed from the timestamp
	unsigned long Random::newSeed()
	{
		Random::updateTimeStamp();
		std::mt19937 generateSeed(Random::_timeStamp);

		static unsigned long seedBounce = 0;

		unsigned long seed = (unsigned long) generateSeed();

		return seed + (seedBounce++);
	}

} // namespace sfew