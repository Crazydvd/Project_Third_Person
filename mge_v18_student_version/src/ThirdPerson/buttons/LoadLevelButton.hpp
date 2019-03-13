#ifndef LOADLEVELBUTTON_HPP
#define LOADLEVELBUTTON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "glm.hpp"
#include "ThirdPerson/buttons/MenuButton.hpp"
#include "ThirdPerson/Room.hpp"
#include "ThirdPerson/UserInterface.hpp"

class LoadLevelButton : public MenuButton
{
public:
	LoadLevelButton(sf::RenderWindow* aWindow, Room* pRoom, UserInterface* pUI, int pLevel, std::string pfileName, std::string hoverFileName, glm::vec2 pPosition, std::string pName = "MenuButton");
	void OnClick();
	virtual ~LoadLevelButton();

private:
	sf::Texture _hoverTexture;
	LoadLevelButton(const LoadLevelButton&);
	LoadLevelButton& operator=(const LoadLevelButton&);

	Room* _room;
	UserInterface* _userInterface;
	int _level;

protected:
};

#endif // LoadLevelButton_HPP
