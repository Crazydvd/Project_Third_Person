#include <cassert>
#include <iostream>

#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include "ThirdPerson/buttons/QuitGameButton.hpp"
#include "ThirdPerson/config.hpp"

QuitGameButton::QuitGameButton(sf::RenderWindow * aWindow, std::string fileName, std::string hoverFileName, glm::vec2 pPosition, std::string pName) : MenuButton(aWindow, fileName, hoverFileName, pPosition, pName)
{

}

void QuitGameButton::OnClick()
{
	MenuButton::OnClick();
	_window->close();
}

QuitGameButton::~QuitGameButton()
{
	//dtor
}
