#include "AudioSource.hpp"

#include <iostream>
#include <fstream>

namespace sfew
{
	// Ctor/Dtor ========================================

	AudioSource::AudioSource(const std::string& audioFilePath, AudioType type) : 
		INameable("Unnamed AudioSource"),
		_audioType(type),
		_playStatus(AudioStatusType::Stopped),
		_flaggedAsLoaded(false)
	{
		std::cout << "Loading audio from \"" << audioFilePath << "\"" << std::endl;
		bool audioLoadSuccessful;

		// Load the audio file as either sound or music
		if(_audioType == AudioType::Sound)
		{
			audioLoadSuccessful = _buffer.loadFromFile(audioFilePath);
			// Sounds need to refer to the SoundBuffer
			_soundEffect.setBuffer(_buffer);
		}
		else if(_audioType == AudioType::Music)
		{
			audioLoadSuccessful = _music.openFromFile(audioFilePath);
			// Usually music is looped
			_music.setLoop(true);
		}

		// Check file load status
		if(!audioLoadSuccessful)
		{
			std::cout << "Error! Audio file does not exist!" << std::endl;
			std::cout << "Any calls to this sound will not play." << std::endl;
			_flaggedAsLoaded = false;
		}
		else
		{
			std::cout << "...Success!" << std::endl;
			_flaggedAsLoaded = true;
		}
}

	AudioSource::~AudioSource()
	{
		
	}

	// Routines =========================================

	void AudioSource::Play()
	{

	}

	void AudioSource::Pause()
	{

	}
	void AudioSource::Stop()
	{

	}

	void AudioSource::Mute()
	{

	}

	void AudioSource::Unmute()
	{

	}

	// Properties =========================================

	void AudioSource::SetLooping(bool loop)
	{

	}

	bool AudioSource::IsLooping() const
	{
		return false;
	}

	void AudioSource::SetVolume(float newVolume)
	{

	}

	float AudioSource::GetVolume() const
	{
		return 0;
	}

	void AudioSource::SetPitch(float newPitch)
	{

	}

	float AudioSource::GetPitch() const
	{
		return 0;
	}

	void AudioSource::SetPlayingOffset(sf::Time newOffset)
	{

	}

	sf::Time AudioSource::GetPlayingOffset() const
	{
		return sf::Time::Zero;
	}
		
	// Getters only

	sf::Time AudioSource::GetDuration() const
	{
		return sf::Time::Zero;
	}

	unsigned int AudioSource::GetChannelCount() const
	{
		return 0;
	}

	unsigned int AudioSource::GetSampleRate() const
	{
		return 0;
	}

	bool AudioSource::IsPlaying() const
	{
		return false;
	}

	bool AudioSource::IsPaused() const
	{
		return false;
	}

	bool AudioSource::IsStopped() const
	{
		return false;
	}

	bool AudioSource::IsMuted() const
	{
		return false;
	}

	// Helpers =========================================

} // namespace sfew