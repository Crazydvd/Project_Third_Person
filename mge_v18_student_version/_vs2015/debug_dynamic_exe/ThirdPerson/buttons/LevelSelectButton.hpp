#ifndef LEVELSELECTBUTTON_HPP
#define LEVELSELECTBUTTON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "glm.hpp"
#include "ThirdPerson/buttons/MenuButton.hpp"
#include "ThirdPerson/TPerson.hpp"
#include "ThirdPerson/Room.hpp"

class LevelSelectButton : public MenuButton
{
public:
	LevelSelectButton(sf::RenderWindow* aWindow, Room* pRoom, TPerson* pGame, std::string pfileName, std::string hoverFileName, glm::vec2 pPosition, std::string pName = "LevelSelectButton");
	void OnClick();
	virtual ~LevelSelectButton();

private:
	Room* _room;
	TPerson* _game;
	sf::Texture _hoverTexture;
	LevelSelectButton(const LevelSelectButton&);
	LevelSelectButton& operator=(const LevelSelectButton&);
protected:
};

#endif // LEVELSELECTBUTTON_HPP
