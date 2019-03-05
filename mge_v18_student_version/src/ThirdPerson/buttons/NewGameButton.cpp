#include <cassert>
#include <iostream>

#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include "ThirdPerson/buttons/NewGameButton.hpp"
#include "ThirdPerson/config.hpp"

NewGameButton::NewGameButton(sf::RenderWindow * aWindow, std::string fileName, std::string hoverFileName, glm::vec2 pPosition, std::string pName) : MenuButton(aWindow, fileName, hoverFileName, pPosition, pName)
{

}

void NewGameButton::OnClick() {
	std::cout << "New game";
}

NewGameButton::~NewGameButton()
{
	//dtor
}
