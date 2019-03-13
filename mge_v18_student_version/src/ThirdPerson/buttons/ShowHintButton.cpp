#include <cassert>
#include <iostream>

#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include "ThirdPerson/buttons/ShowHintButton.hpp"
#include "ThirdPerson/config.hpp"

ShowHintButton::ShowHintButton(sf::RenderWindow * aWindow, UITexture* pTexture, bool* pShowingHint, float* pTimer, std::string fileName, std::string hoverFileName, glm::vec2 pPosition, std::string pName) : MenuButton(aWindow, fileName, hoverFileName, pPosition, pName), _texture(pTexture), _showingHint(pShowingHint), _timer(pTimer)
{

}

void ShowHintButton::OnClick() {
	*_showingHint = true;
	_texture->Enabled = true;
	*_timer = 1;
}

ShowHintButton::~ShowHintButton()
{
	//dtor
}
