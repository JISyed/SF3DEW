// CLASS NAME
// DESCRIPTION
//
// Written by Jibran Syed (MONTH-DAY-YEAR)

#ifndef AUDIO_SOURCE_H
#define AUDIO_SOURCE_H

#include <SFML/Audio.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <string>

#include "INameable.hpp"

namespace sfew
{
	enum class AudioType : char
	{
		Sound,
		Music
	};

	class AudioSource : sf::NonCopyable, public INameable
	{
	public:

		// Ctor/Dtor ======================

		AudioSource(const std::string& vertexShaderPath, AudioType type);
		~AudioSource();

		// Routines =======================

		

		// Properties =====================

	private:

		// Helpers ========================

		

		// Data ===========================

		AudioType _audioType;		// Is the audio a sound effect or music?
		sf::SoundBuffer _buffer;	// Data buffer for sounds only
		sf::Sound _soundEffect;		// The sound effect delegation
		sf::Music _music;			// The music delegation

		// Flags ==========================

		bool _flaggedAsLoaded;		// Was the audio file successfully loaded?
	};

	
} // namespace sfew

#endif