#ifndef NEWGAMEBUTTON_HPP
#define NEWGAMEBUTTON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "glm.hpp"
#include "ThirdPerson/buttons/MenuButton.hpp"
#include "ThirdPerson/Room.hpp"
#include "ThirdPerson/UserInterface.hpp"

class NewGameButton : public MenuButton
{
public:
	NewGameButton(sf::RenderWindow* aWindow, Room* pRoom, UserInterface* pUI, std::string pfileName, std::string hoverFileName, glm::vec2 pPosition, std::string pName = "MenuButton");
	void OnClick();
	virtual ~NewGameButton();

private:
	sf::Texture _hoverTexture;
	NewGameButton(const NewGameButton&);
	NewGameButton& operator=(const NewGameButton&);

	Room* _room;
	UserInterface* _userInterface;

protected:
};

#endif // NEWGAMEBUTTON_HPP
