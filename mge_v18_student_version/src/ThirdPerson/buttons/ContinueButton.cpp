#include <cassert>
#include <iostream>

#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include "ThirdPerson/buttons/ContinueButton.hpp"
#include "ThirdPerson/config.hpp"

ContinueButton::ContinueButton(sf::RenderWindow * aWindow, std::string fileName, std::string hoverFileName, glm::vec2 pPosition, std::string pName) : MenuButton(aWindow, fileName, hoverFileName, pPosition, pName)
{

}

void ContinueButton::OnClick() {
	std::cout << "continue";
}

ContinueButton::~ContinueButton()
{
	//dtor
}
