#include "ThirdPerson/Audio.hpp"

Audio::Audio(SoundType pType, std::string pFilePath) : _type(pType)
{
	if (_type == SoundType::SOUND)
	{
		_buffer.loadFromFile(pFilePath);
		_sound.setBuffer(_buffer);
	}
	else
	{
		_music.openFromFile(pFilePath);
	}
}

void Audio::Play()
{
	if (_type == SoundType::SOUND)
	{
		_sound.play();
	}
	else
	{
		_music.play();
	}
}

void Audio::Pause()
{
	if (_type == SoundType::SOUND)
	{
		_sound.pause();
	}
	else
	{
		_music.pause();
	}
}

void Audio::Stop()
{
	if (_type == SoundType::SOUND)
	{
		_sound.stop();
	}
	else
	{
		_music.stop();
	}
}

sf::SoundSource::Status Audio::GetStatus()
{
	if (_type == SoundType::SOUND)
	{
		return _sound.getStatus();
	}
	else
	{
		return _music.getStatus();
	}
}

void Audio::SetPitch(float pPitch)
{
	if (_type == SoundType::SOUND)
	{
		_sound.setPitch(pPitch);
	}
	else
	{
		_music.setPitch(pPitch);
	}
}

void Audio::SetPlayingOffset(sf::Time pSeconds)
{
	if (_type == SoundType::SOUND)
	{
		_sound.setPlayingOffset(pSeconds);
	}
	else
	{
		_music.setPlayingOffset(pSeconds);
	}
}

void Audio::SetVolume(float pVolume)
{
	if (_type == SoundType::SOUND)
	{
		_sound.setVolume(pVolume);
	}
	else
	{
		_music.setVolume(pVolume);
	}
}

void Audio::SetLoop(bool pLoop)
{
	if (_type == SoundType::SOUND)
	{
		_sound.setLoop(pLoop);
	}
	else
	{
		_music.setLoop(pLoop);
	}
}