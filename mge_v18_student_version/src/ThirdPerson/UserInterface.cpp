#include <cassert>
#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio/Music.hpp>
#include "ThirdPerson/UserInterface.hpp"
#include "ThirdPerson/buttons/NewGameButton.hpp"
#include "ThirdPerson/buttons/QuitGameButton.hpp"
#include "ThirdPerson/buttons/LevelSelectButton.hpp"
#include "ThirdPerson/buttons/ContinueButton.hpp"
#include "ThirdPerson/buttons/LoadLevelButton.hpp"
#include "ThirdPerson/buttons/BackToMainButton.hpp"
#include "ThirdPerson/config.hpp"

UserInterface::UserInterface(sf::RenderWindow * aWindow, std::string pName, glm::vec3 pPosition)
	: GameObject(pName, pPosition), _window(aWindow)
{
	assert(_window != NULL);
	UserInterface::_objects = std::vector<UITexture*>();
}

void UserInterface::update(float pStep) {
	if (Paused)
		return;
	
	sf::Vector2i mousePos = sf::Mouse::getPosition(*_window);
	//check for hovering over objects
	for (int i = _buttons.size() - 1; i > -1; i--) {
		sf::Vector2f objPos = _buttons[i]->GetPosition();
		sf::IntRect objRect = _buttons[i]->GetRect();

		if ((mousePos.x > objPos.x) && (mousePos.x < objPos.x + objRect.width) &&
			(mousePos.y > objPos.y) && (mousePos.y < objPos.y + objRect.height))
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				_buttons[i]->OnClick();
			}
			if (_buttons.size() < i + 1 || _buttons.size() > 100) 
				return; // be gone if the thot is gone

			_buttons[i]->OnHover();
		}
		else if (_buttons[i]->_hovering) {
			_buttons[i]->OnStopHover();
		}
	}

	if (_queueClearing) {
		EmptyInterface();
		_queueClearing = false;
	}
}


void UserInterface::Add(UITexture* pObject) {
	_objects.push_back(pObject);
}

void UserInterface::AddButton(MenuButton* pObject) {
	_buttons.push_back(pObject);
}

void UserInterface::draw()
{
	for (size_t i = 0; i < _objects.size(); i++) {
		if (i < _objects.size()) {
			_objects[i]->draw();
		}
	}

	for (size_t i = 0; i < _buttons.size(); i++) {
		if (i < _buttons.size()) {
			_buttons[i]->draw();
		}
	}
}

void UserInterface::LoadMainMenu(Room* pRoom, TPerson* pGame) {
	EmptyInterface();

	UITexture* corkBoard = new UITexture(_window, "corkboard.png");

	
	_level1 = new UITexture(_window, "1formenudark.png", glm::vec2(760, 10));
	_level2 = new UITexture(_window, "2formenudark.png", glm::vec2(1530, 520));
	_level3 = new UITexture(_window, "3formenudark.png", glm::vec2(1135, 300));
	_level4 = new UITexture(_window, "4formenudark.png", glm::vec2(775, 400));
	_level5 = new UITexture(_window, "5formenudark.png", glm::vec2(1450, 18));
	_string = new UITexture(_window, "yarnonly.png", glm::vec2(0, 0));


	NewGameButton* newGame = new NewGameButton(_window, pRoom, this, "New_Game.png", "New_Game_selected.png", glm::vec2(100, 40));
	ContinueButton* continueButton = new ContinueButton(_window, pRoom, this, "continue.png", "Continue_selected.png", glm::vec2(100, 300));
	LevelSelectButton* levelSelect = new LevelSelectButton(_window, pRoom, pGame, "level_select.png", "level_select_selected.png", glm::vec2(100, 620));
	QuitGameButton* quitGame = new QuitGameButton(_window, "quitpin.png", "quitselected.png", glm::vec2(550, 700));

	Add(corkBoard);
	Add(_level1);
	Add(_level2);
	Add(_level3);
	Add(_level4);
	Add(_level5);
	Add(_string);
	AddButton(newGame);
	AddButton(continueButton);
	AddButton(levelSelect);
	AddButton(quitGame);
}

void UserInterface::LoadLevelSelect(Room* pRoom, TPerson* pGame) {
	EmptyInterface();

	UITexture* corkBoard = new UITexture(_window, "corkboard.png");
	Add(corkBoard);

	BackToMainButton* backButton = new BackToMainButton(_window, pRoom, pGame, "backlevelselect.png", "backselectedlevelselect.png", glm::vec2(100, 600));
	AddButton(backButton);

	int level = 1;
	std::string line;

	std::ifstream myfile("save.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			std::cout << line;
			level = std::stoi(line);
		}
		myfile.close();
	}
	std::vector<UITexture*> polaroids = std::vector<UITexture*> { _level1, _level2, _level3, _level4, _level5 };
	int index = 0;
	while (level > 0) {
		level -= 2;
		LoadLevelButton* button = new LoadLevelButton(_window,
														pRoom,
														this,
														(1 + index * 2),
														std::to_string(index + 1) + "formenu.png",
														std::to_string(index + 1) + "formenudark.png",
														glm::vec2(polaroids[index]->GetPosition().x, polaroids[index]->GetPosition().y));
		AddButton(button);
		index++;
	}

	while (index < 5) {
		Add(polaroids[index]);
		index++;
	}
		
	Add(_string); // Overlay dem string boi
}

// queue it instead of doing it immediatly so it doesn't interfere with the update loop
void UserInterface::QueueClear() {
	_queueClearing = true;
}

void UserInterface::EmptyInterface() {
	_objects.clear();
	_buttons.clear();
}

UserInterface::~UserInterface()
{
	//dtor
}
