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

	void Play(); //Plays the audio
	void Pause(); //Pauses the audio
	void Stop(); //Stops playing the audio and resets position to beginning
	sf::SoundSource::Status GetStatus(); //Get the current status of the audio (stopped, paused, playing)
	
	void SetPitch(float pPitch); //Set the pitch of the audio (also changes playback speed)
	void SetPlayingOffset(sf::Time pSeconds); //Set the current position in the audio file (e.g. start playing at 1 minute)
	void SetVolume(float pVolume); //Set the volume of the audio [0 - 100]; default is 100
	void SetLoop(bool pLoop); //Set whether the audio loops or not


private:
	SoundType _type;

	sf::SoundBuffer _buffer;
	sf::Sound _sound;
	sf::Music _music;
};

#endif // !AUDIO_HPP