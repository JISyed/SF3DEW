#include "AudioSource.hpp"

#include <iostream>
#include <fstream>

namespace sfew
{
	// Ctor/Dtor ========================================

	AudioSource::AudioSource(const std::string& vertexShaderPath, AudioType type) : 
		INameable("Unnamed AudioSource"),
		_audioType(type),
		_flaggedAsLoaded(false)
	{
		
	}

	AudioSource::~AudioSource()
	{
		
	}

	// Routines =========================================

	// Properties =========================================

	// Helpers =========================================

} // namespace sfew