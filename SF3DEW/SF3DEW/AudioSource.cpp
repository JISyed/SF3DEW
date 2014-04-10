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
		// Make sure audio was successfully loaded
		if(!_flaggedAsLoaded) return;


	}

	void AudioSource::Pause()
	{
		// Make sure audio was successfully loaded
		if(!_flaggedAsLoaded) return;


	}
	void AudioSource::Stop()
	{
		// Make sure audio was successfully loaded
		if(!_flaggedAsLoaded) return;


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
		if(_audioType == AudioType::Sound)
		{
			_soundEffect.setLoop(loop);
		}
		else if(_audioType == AudioType::Music)
		{
			_music.setLoop(loop);
		}
	}

	bool AudioSource::IsLooping() const
	{
		bool wasLooping;

		if(_audioType == AudioType::Sound)
		{
			wasLooping = _soundEffect.getLoop();
		}
		else if(_audioType == AudioType::Music)
		{
			wasLooping = _music.getLoop();
		}

		return wasLooping;
	}

	void AudioSource::SetVolume(float newVolume)
	{
		// Restrict volume between 0 and 100
		if(newVolume < 0.0f)
		{
			newVolume = 0.0f;
		}
		if(newVolume > 100.0f)
		{
			newVolume = 100.0f;
		}

		// Set new volume
		if(_audioType == AudioType::Sound)
		{
			_soundEffect.setVolume(newVolume);
		}
		else if(_audioType == AudioType::Music)
		{
			_music.setVolume(newVolume);
		}
	}

	float AudioSource::GetVolume() const
	{
		float volumeLevel;

		if(_audioType == AudioType::Sound)
		{
			volumeLevel = _soundEffect.getVolume();
		}
		else if(_audioType == AudioType::Music)
		{
			volumeLevel = _music.getVolume();
		}

		return volumeLevel;
	}

	void AudioSource::SetPitch(float newPitch)
	{
		// Restrict pitch between 0.01 and 100
		if(newPitch < 0.01f)
		{
			newPitch = 0.01f;
		}
		if(newPitch > 100.0f)
		{
			newPitch = 100.0f;
		}

		// Set new pitch
		if(_audioType == AudioType::Sound)
		{
			_soundEffect.setPitch(newPitch);
		}
		else if(_audioType == AudioType::Music)
		{
			_music.setPitch(newPitch);
		}
	}

	float AudioSource::GetPitch() const
	{
		float pitchLevel;

		if(_audioType == AudioType::Sound)
		{
			pitchLevel = _soundEffect.getPitch();
		}
		else if(_audioType == AudioType::Music)
		{
			pitchLevel = _music.getPitch();
		}

		return pitchLevel;
	}

	void AudioSource::SetPlayingOffset(sf::Time newOffset)
	{
		if(_audioType == AudioType::Sound)
		{
			_soundEffect.setPlayingOffset(newOffset);
		}
		else if(_audioType == AudioType::Music)
		{
			_music.setPlayingOffset(newOffset);
		}
	}

	sf::Time AudioSource::GetPlayingOffset() const
	{
		sf::Time playingOffset;

		if(_audioType == AudioType::Sound)
		{
			playingOffset = _soundEffect.getPlayingOffset();
		}
		else if(_audioType == AudioType::Music)
		{
			playingOffset = _music.getPlayingOffset();
		}

		return playingOffset;
	}
		
	// Getters only

	sf::Time AudioSource::GetDuration() const
	{
		sf::Time duration;

		if(_audioType == AudioType::Sound)
		{
			duration = _buffer.getDuration();
		}
		else if(_audioType == AudioType::Music)
		{
			duration = _music.getDuration();
		}

		return duration;
	}

	unsigned int AudioSource::GetChannelCount() const
	{
		unsigned int numOfChannels;

		if(_audioType == AudioType::Sound)
		{
			numOfChannels = _buffer.getChannelCount();
		}
		else if(_audioType == AudioType::Music)
		{
			numOfChannels = _music.getChannelCount();
		}

		return numOfChannels;
	}

	unsigned int AudioSource::GetSampleRate() const
	{
		unsigned int sampleRate;

		if(_audioType == AudioType::Sound)
		{
			sampleRate = _buffer.getSampleRate();
		}
		else if(_audioType == AudioType::Music)
		{
			sampleRate = _music.getSampleRate();
		}

		return sampleRate;
	}

	bool AudioSource::IsPlaying() const
	{
		return _playStatus == AudioStatusType::Playing;
	}

	bool AudioSource::IsPaused() const
	{
		return _playStatus == AudioStatusType::Paused;
	}

	bool AudioSource::IsStopped() const
	{
		return _playStatus == AudioStatusType::Stopped;
	}

	bool AudioSource::IsMuted() const
	{
		return _playStatus == AudioStatusType::Muted;
	}

	// Helpers =========================================

} // namespace sfew