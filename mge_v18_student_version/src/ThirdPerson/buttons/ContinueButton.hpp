#ifndef CONTINUEBUTTON_HPP
#define CONTINUEBUTTON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "glm.hpp"
#include "ThirdPerson/buttons/MenuButton.hpp"

class ContinueButton : public MenuButton
{
public:
	ContinueButton(sf::RenderWindow* aWindow, std::string pfileName, std::string hoverFileName, glm::vec2 pPosition, std::string pName = "QuitMenuButton");
	void OnClick();
	virtual ~ContinueButton();

private:
	sf::Texture _hoverTexture;
	ContinueButton(const ContinueButton&);
	ContinueButton& operator=(const ContinueButton&);
protected:
};

#endif // NEWGAMEBUTTON_HPP
