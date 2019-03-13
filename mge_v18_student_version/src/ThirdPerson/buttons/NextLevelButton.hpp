#ifndef NEXTLEVELBUTTON_HPP
#define NEXTLEVELBUTTON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "glm.hpp"
#include "ThirdPerson/buttons/MenuButton.hpp"
#include "ThirdPerson/TPerson.hpp"
#include "ThirdPerson/Room.hpp"
#include "ThirdPerson/UserInterface.hpp"
#include "ThirdPerson/Puzzle.hpp"

class NextLevelButton : public MenuButton
{
public:
	NextLevelButton(sf::RenderWindow* aWindow, Room* pRoom, Puzzle* pPuzzle, UserInterface* pUI, int pLevelIndex, float* pTimer, bool* pEnd, std::string pfileName, std::string hoverFileName, glm::vec2 pPosition, std::string pName = "NextLevelButton");
	void OnClick();
	virtual ~NextLevelButton();

private:
	sf::Texture _hoverTexture;
	NextLevelButton(const NextLevelButton&);
	NextLevelButton& operator=(const NextLevelButton&);
	Room* _room;
	UserInterface* _UI;
	int _level;
	float* _endTimer;
	bool* _endBool;
	Puzzle* _puzzle;

protected:
};

#endif // NEWGAMEBUTTON_HPP
