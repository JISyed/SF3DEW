#include "AudioSource.hpp"

#include <iostream>

namespace sfew
{
	// Ctor/Dtor ========================================

	// Ctor
	AudioSource::AudioSource(const std::string& audioFilePath, AudioType type) : 
		INameable("Unnamed AudioSource"),
		_audioType(type),
		_playStatus(AudioStatusType::Stopped),
		_volBeforeMute(100.0f),
		_statusBeforeMute(AudioStatusType::Muted),
		_flaggedAsLoaded(false),
		_isInteruptable(true)
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

	// Dtor
	AudioSource::~AudioSource()
	{
		Stop();
	}

	// Routines =========================================

	void AudioSource::Play()
	{
		// Make sure audio was successfully loaded
		if(!_flaggedAsLoaded) return;

		// Update the audio state based off internal SFML state
		updatePlayStatus();

		// Automatically unmute
		Unmute();

		// Play audio
		if(_playStatus != AudioStatusType::Playing)
		{
			if(_audioType == AudioType::Sound)
			{
				_soundEffect.play();
			}
			else if(_audioType == AudioType::Music)
			{
				_music.play();
			}

			_playStatus = AudioStatusType::Playing;
		}
	}

	void AudioSource::Pause()
	{
		// Make sure audio was successfully loaded
		if(!_flaggedAsLoaded) return;

		// Update the audio state based off internal SFML state
		updatePlayStatus();

		// Pause audio
		if(_playStatus != AudioStatusType::Paused)
		{
			if(_audioType == AudioType::Sound)
			{
				_soundEffect.pause();
			}
			else if(_audioType == AudioType::Music)
			{
				_music.pause();
			}

			_playStatus = AudioStatusType::Paused;
		}
	}

	void AudioSource::Stop()
	{
		// Make sure audio was successfully loaded
		if(!_flaggedAsLoaded) return;

		// Update the audio state based off internal SFML state
		updatePlayStatus();

		// Stop audio
		if(_playStatus != AudioStatusType::Stopped)
		{
			if(_audioType == AudioType::Sound)
			{
				_soundEffect.stop();
			}
			else if(_audioType == AudioType::Music)
			{
				_music.stop();
			}

			_playStatus = AudioStatusType::Stopped;
		}
	}

	void AudioSource::Mute()
	{
		// Mute audio and remember previous volume and status
		if(_playStatus != AudioStatusType::Muted)
		{
			_volBeforeMute = GetVolume();
			_statusBeforeMute = _playStatus;

			_playStatus = AudioStatusType::Muted;

			SetVolume(0.0f);
		}
	}

	void AudioSource::Unmute()
	{
		// Unmute by applying previous volume and status
		if(_playStatus == AudioStatusType::Muted)
		{
			SetVolume(_volBeforeMute);
			_playStatus = _statusBeforeMute;
			_statusBeforeMute = AudioStatusType::Muted;
		}
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
		// Restrict pitch between 0.05 and 50
		if(newPitch < 0.05f)
		{
			newPitch = 0.05f;
		}
		if(newPitch > 50.0f)
		{
			newPitch = 50.0f;
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
		return (_playStatus == AudioStatusType::Playing) 
			|| (_statusBeforeMute == AudioStatusType::Playing);
	}

	bool AudioSource::IsPaused() const
	{
		return (_playStatus == AudioStatusType::Paused) 
			|| (_statusBeforeMute == AudioStatusType::Paused);
	}

	bool AudioSource::IsStopped() const
	{
		return (_playStatus == AudioStatusType::Stopped) 
			|| (_statusBeforeMute == AudioStatusType::Stopped);
	}

	bool AudioSource::IsMuted() const
	{
		return _playStatus == AudioStatusType::Muted;
	}

	void AudioSource::SetInteruptability(bool willBeInteruptable)
	{
		_isInteruptable = willBeInteruptable;
	}

	bool AudioSource::IsInteruptable() const
	{
		return _isInteruptable;
	}

	// Helpers =========================================

	// Get play state directly from SFML
	sf::SoundSource::Status AudioSource::getInternalStatus() const
	{
		sf::SoundSource::Status audioStatus;

		if(_audioType == AudioType::Sound)
		{
			audioStatus = _soundEffect.getStatus();
		}
		else if(_audioType == AudioType::Music)
		{
			audioStatus = _music.getStatus();
		}

		return audioStatus;
	}

	// Retrive play status from SFML to update AudioSource's status
	void AudioSource::updatePlayStatus()
	{
		sf::SoundSource::Status internalStatus = getInternalStatus();

		if(_playStatus == AudioStatusType::Muted)
		{
			switch (internalStatus)
			{
			case sf::SoundSource::Stopped:
				_statusBeforeMute = AudioStatusType::Stopped;
				break;
			case sf::SoundSource::Paused:
				_statusBeforeMute = AudioStatusType::Paused;
				break;
			case sf::SoundSource::Playing:
				_statusBeforeMute = AudioStatusType::Playing;
				break;
			default:
				break;
			}
		}
		else
		{
			switch (internalStatus)
			{
			case sf::SoundSource::Stopped:
				_playStatus = AudioStatusType::Stopped;
				break;
			case sf::SoundSource::Paused:
				_playStatus = AudioStatusType::Paused;
				break;
			case sf::SoundSource::Playing:
				_playStatus = AudioStatusType::Playing;
				break;
			default:
				break;
			}
		}
	}

} // namespace sfew