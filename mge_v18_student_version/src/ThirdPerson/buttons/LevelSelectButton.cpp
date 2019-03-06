#include <cassert>
#include <iostream>

#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include "ThirdPerson/buttons/LevelSelectButton.hpp"
#include "ThirdPerson/config.hpp"

LevelSelectButton::LevelSelectButton(sf::RenderWindow * aWindow, std::string fileName, std::string hoverFileName, glm::vec2 pPosition, std::string pName) : MenuButton(aWindow, fileName, hoverFileName, pPosition, pName)
{

}

void LevelSelectButton::OnClick() {
	std::cout << "level select";
}

LevelSelectButton::~LevelSelectButton()
{
	//dtor
}
