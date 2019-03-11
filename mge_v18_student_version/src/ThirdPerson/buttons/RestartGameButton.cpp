#include <cassert>
#include <iostream>

#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include "ThirdPerson/buttons/RestartGameButton.hpp"
#include "ThirdPerson/config.hpp"

RestartGameButton::RestartGameButton(sf::RenderWindow * aWindow, Room* pRoom, std::string fileName, std::string hoverFileName, glm::vec2 pPosition, std::string pName) : MenuButton(aWindow, fileName, hoverFileName, pPosition, pName), _room(pRoom)
{

}

void RestartGameButton::OnClick() {
	_room->TogglePause();
	_room->LoadLevel(0, true);
}

RestartGameButton::~RestartGameButton()
{
	//dtor
}
