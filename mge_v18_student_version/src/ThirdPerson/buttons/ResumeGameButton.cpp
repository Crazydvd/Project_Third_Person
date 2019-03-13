#include <cassert>
#include <iostream>

#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include "ThirdPerson/buttons/ResumeGameButton.hpp"
#include "ThirdPerson/config.hpp"

ResumeGameButton::ResumeGameButton(sf::RenderWindow * aWindow, Room* pRoom, std::string fileName, std::string hoverFileName, glm::vec2 pPosition, std::string pName) : MenuButton(aWindow, fileName, hoverFileName, pPosition, pName), _room(pRoom)
{

}

void ResumeGameButton::OnClick()
{
	MenuButton::OnClick();
	_room->TogglePause();
}

ResumeGameButton::~ResumeGameButton()
{
	//dtor
}
