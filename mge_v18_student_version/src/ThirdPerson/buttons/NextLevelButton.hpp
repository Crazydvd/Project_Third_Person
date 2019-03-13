#ifndef NEXTLEVELBUTTON_HPP
#define NEXTLEVELBUTTON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "glm.hpp"
#include "ThirdPerson/buttons/MenuButton.hpp"
#include "ThirdPerson/TPerson.hpp"
#include "ThirdPerson/Room.hpp"

class NextLevelButton : public MenuButton
{
public:
	NextLevelButton(sf::RenderWindow* aWindow, Room* pRoom, std::string pfileName, std::string hoverFileName, glm::vec2 pPosition, std::string pName = "NextLevelButton");
	void OnClick();
	virtual ~NextLevelButton();

private:
	sf::Texture _hoverTexture;
	NextLevelButton(const NextLevelButton&);
	NextLevelButton& operator=(const NextLevelButton&);
	Room* _room;
protected:
};

#endif // NEWGAMEBUTTON_HPP
