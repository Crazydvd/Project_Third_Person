#include <cassert>
#include <iostream>

#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include "ThirdPerson/buttons/NextLevelButton.hpp"
#include "ThirdPerson/config.hpp"

NextLevelButton::NextLevelButton(sf::RenderWindow * aWindow, Room* pRoom, Puzzle* pPuzzle, UserInterface* pUI, int pLevelIndex, float* pTimer, bool* pEnd, std::string fileName, std::string hoverFileName, glm::vec2 pPosition, std::string pName) : MenuButton(aWindow, fileName, hoverFileName, pPosition, pName), _room(pRoom), _level(pLevelIndex), _UI(pUI), _endTimer(pTimer), _endBool(pEnd), _puzzle(pPuzzle)
{

}

void NextLevelButton::OnClick() {
	if (_level < 10) {
		_room->MoveToNextLevel();
	}
	else {
		_puzzle->PuzzleTimer->SetPosition(glm::vec2(200000,20000));
		_UI->EmptyInterface();
		*_endBool = true;
		*_endTimer = 5;
		UITexture* endScreen = new UITexture(_window, "StoryEnding.png");
		endScreen->SetPosition(glm::vec2(0, 0));
		_UI->Add(endScreen);
	}
}

NextLevelButton::~NextLevelButton()
{
	//dtor
}
