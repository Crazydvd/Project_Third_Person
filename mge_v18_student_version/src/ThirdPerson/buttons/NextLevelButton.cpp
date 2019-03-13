#include <cassert>
#include <iostream>

#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include "ThirdPerson/buttons/NextLevelButton.hpp"
#include "ThirdPerson/config.hpp"

NextLevelButton::NextLevelButton(sf::RenderWindow * aWindow, Room* pRoom, std::string fileName, std::string hoverFileName, glm::vec2 pPosition, std::string pName) : MenuButton(aWindow, fileName, hoverFileName, pPosition, pName), _room(pRoom)
{

}

void NextLevelButton::OnClick() {
	_room->MoveToNextLevel();
}

NextLevelButton::~NextLevelButton()
{
	//dtor
}
