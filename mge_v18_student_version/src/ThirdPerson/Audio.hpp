#ifndef AUDIO_HPP
#define AUDIO_HPP = 2;
#include "SFML/Audio.hpp"

enum SoundType
{
	SOUND,
	MUSIC,
};

class Audio
{
public:
	Audio(SoundType pType, std::string pFilePath);
	~Audio();

	void Play();
	void Pause();
	void Stop();
	sf::SoundSource::Status GetStatus();
	
	void SetPitch(float pPitch);
	void SetPlayingOffset(sf::Time pSeconds);
	void SetVolume(float pVolume);
	void SetLoop(bool pLoop);


private:
	SoundType _type;

	sf::SoundBuffer _buffer;
	sf::Sound _sound;
	sf::Music _music;
};

#endif // !AUDIO_HPP