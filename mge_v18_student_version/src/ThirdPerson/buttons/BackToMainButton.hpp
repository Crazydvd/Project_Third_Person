#ifndef BACKTOMAINBUTTON_HPP
#define BACKTOMAINBUTTON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "glm.hpp"
#include "ThirdPerson/buttons/MenuButton.hpp"
#include "ThirdPerson/TPerson.hpp"
#include "ThirdPerson/Room.hpp"

class BackToMainButton : public MenuButton
{
public:
	BackToMainButton(sf::RenderWindow* aWindow, Room* pRoom, TPerson* pGame, std::string pfileName, std::string hoverFileName, glm::vec2 pPosition, std::string pName = "QuitMenuButton");
	void OnClick();
	virtual ~BackToMainButton();

private:
	sf::Texture _hoverTexture;
	BackToMainButton(const BackToMainButton&);
	BackToMainButton& operator=(const BackToMainButton&);
	Room* _room;
	TPerson* _game;
protected:
};

#endif // NEWGAMEBUTTON_HPP
