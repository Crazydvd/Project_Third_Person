#ifndef TIMER_HPP
#define TIMER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

/**
 * Very simple class capable of rendering a simple piece of text through SFML.
 */
class Timer
{
public:
	Timer(sf::RenderWindow * aWindow);
	virtual ~Timer();
	float GetTime();
	void SetTime(float pTime);
	void draw();

private:
	sf::RenderWindow * _window;

	std::string _timerInfo;

	sf::Font _font;
	sf::Text _timerText;

	float _time;

	void _createTimer();

	Timer(const Timer&);
	Timer& operator=(const Timer&);

};

#endif // TIMER_HPP
