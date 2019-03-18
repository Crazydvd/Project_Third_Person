#ifndef RETURNTOMENUBUTTON_HPP
#define RETURNTOMENUBUTTON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "glm.hpp"
#include "ThirdPerson/buttons/MenuButton.hpp"
#include "ThirdPerson/TPerson.hpp"
#include "ThirdPerson/Room.hpp"

class ReturnToMenuButton : public MenuButton
{
public:
	ReturnToMenuButton(sf::RenderWindow* aWindow, Room* pRoom, TPerson* pGame, std::string pfileName, std::string hoverFileName, glm::vec2 pPosition, std::string pName = "QuitMenuButton");
	void OnClick();
	virtual ~ReturnToMenuButton();

private:
	sf::Texture _hoverTexture;
	ReturnToMenuButton(const ReturnToMenuButton&);
	ReturnToMenuButton& operator=(const ReturnToMenuButton&);
	Room* _room;
	TPerson* _game;
protected:
};

#endif // NEWGAMEBUTTON_HPP
