#ifndef RESTARTGAMEBUTTON_HPP
#define RESTARTGAMEBUTTON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "glm.hpp"
#include "ThirdPerson/buttons/MenuButton.hpp"
#include "ThirdPerson/Room.hpp"

class RestartGameButton : public MenuButton
{
public:
	RestartGameButton(sf::RenderWindow* aWindow, Room* pRoom, std::string pfileName, std::string hoverFileName, glm::vec2 pPosition, std::string pName = "QuitMenuButton");
	void OnClick();
	virtual ~RestartGameButton();

private:
	sf::Texture _hoverTexture;
	RestartGameButton(const RestartGameButton&);
	RestartGameButton& operator=(const RestartGameButton&);
	Room* _room;
protected:
};

#endif // NEWGAMEBUTTON_HPP
