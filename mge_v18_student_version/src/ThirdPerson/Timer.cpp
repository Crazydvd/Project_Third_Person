#include <cassert>
#include <iostream>

#include <GL/glew.h>
#include <SFML/Graphics/Text.hpp>
#include "Timer.hpp"
#include "ThirdPerson/config.hpp"

Timer::Timer(sf::RenderWindow * aWindow) : _window(aWindow), _timerInfo(), _font(), _timerText()
{
	assert(_window != NULL);

	if (!_font.loadFromFile(config::THIRDPERSON_FONT_PATH + "topsecretfont.ttf")) {
		std::cout << "Could not load font, exiting..." << std::endl;
		return;
	}

	_createTimer();
}

Timer::~Timer()
{
	//dtor
}

void Timer::_createTimer() {
	_time = 0;
	_timerText.setString("");
	_timerText.setFont(_font);
	_timerText.setCharacterSize(56);
	_timerText.setFillColor(sf::Color::White);
	_timerText.setPosition(10, 100);
}

void Timer::SetPosition(glm::vec2 pPos) {
	_timerText.setPosition(pPos.x, pPos.y);
}

void Timer::SetRotation(float pDeg) {
	_timerText.rotate(pDeg);
}

void Timer::SetTime(float pTime, bool pText) {
	_time = pTime;
	if (pText) {
		_timerText.setString(std::to_string((int)_time) + " seconds");
	}
	else {
		_timerText.setString(std::to_string((int)_time));
	}
}

void Timer::SetFont(std::string pFont) {
	if (!_font.loadFromFile(config::THIRDPERSON_FONT_PATH + pFont)) {
		std::cout << "Could not load font, exiting..." << std::endl;
		return;
	}
	_timerText.setFont(_font);
}

void Timer::SetColor(sf::Color pColor) {
	_timerText.setFillColor(pColor);
}

void Timer::SetFontSize(int pSize) {
	_timerText.setCharacterSize(pSize);
}

float Timer::GetTime() {
	return _time;
}

void Timer::draw()
{
	//glDisable( GL_CULL_FACE );
	glActiveTexture(GL_TEXTURE0);
	_window->pushGLStates();
	_window->draw(_timerText);
	_window->popGLStates();
}
