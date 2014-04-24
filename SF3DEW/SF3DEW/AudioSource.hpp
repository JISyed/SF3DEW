// AudioSource
// Wrapper for SFML audio functionality
// Allows to store either a sfx or music without different classes
// Only supports 2D audio (no spacialization)
//
// Written by Jibran Syed (4-10-2014)

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

	enum class AudioStatusType : char
	{
		Playing,
		Paused,
		Stopped,
		Muted
	};

	class AudioSource : sf::NonCopyable, public INameable
	{
	public:

		// Ctor/Dtor ======================

		AudioSource(const std::string& audioFilePath, AudioType type);
		virtual ~AudioSource();

		// Routines =======================

		void Play();
		void Pause();
		void Stop();
		void Mute();
		void Unmute();

		// Properties =====================

		void SetLooping(bool loop);
		bool IsLooping() const;
		void SetVolume(float newVolume);
		float GetVolume() const;
		void SetPitch(float newPitch);
		float GetPitch() const;
		void SetPlayingOffset(sf::Time newOffset);
		sf::Time GetPlayingOffset() const;
		
		sf::Time GetDuration() const;
		unsigned int GetChannelCount() const;
		unsigned int GetSampleRate() const;

		bool IsPlaying() const;
		bool IsPaused() const;
		bool IsStopped() const;
		bool IsMuted() const;

		void SetInteruptability(bool willBeInteruptable);
		bool IsInteruptable() const;

	private:

		// Helpers ========================

		sf::SoundSource::Status getInternalStatus() const;	// Get play state directly from SFML
		void updatePlayStatus();	// Retrive play status from SFML to update AudioSource's status

		// Data ===========================

		AudioType _audioType;		// Is the audio a sound effect or music?
		AudioStatusType _playStatus;// The play state of the audio (play, pause, etc)
		sf::SoundBuffer _buffer;	// Data buffer for sound only (not music)
		sf::Sound _soundEffect;		// The sound effect delegation
		sf::Music _music;			// The music delegation
		
		float _volBeforeMute;				// Volume before muting started
		AudioStatusType _statusBeforeMute;	// Play state before muting started

		bool _isInteruptable;		// Will audio stop upon loading a new scene?

		// Flags ==========================

		bool _flaggedAsLoaded;		// Was the audio file successfully loaded?
	};

	
} // namespace sfew

#endif