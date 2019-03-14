#ifndef ROOM_HPP
#define ROOM_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>
#include <lua.hpp>
#include "glm.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Light.hpp"
#include "ThirdPerson/Timer.hpp"
#include "ThirdPerson/Puzzle.hpp"
#include "ThirdPerson/UserInterface.hpp"

class TPerson;
class RenderToTexture;

class Room : public GameObject
{
public:
	Room(TPerson* pGame, World* pWorld, sf::RenderWindow* pWindow, RenderToTexture* pRender, std::string pName = "room",
		glm::vec3 pPosition = glm::vec3(0.0f, 0.0f, 0.0f));
	virtual ~Room();
	virtual void update(float pStep);
	virtual void _render();

	void Initialize();
	void Deinitialize();
	void TogglePause();
	void DisablePause();
	void LoadLevel(int pLevel = 1, bool pReload = false);
	void MoveToNextLevel();
	void MoveToPreviousLevel();

	void PlayAnimation(std::string pName, bool pReverse);

private:
	void loadRoom();
	void saveLevel();
	void print_table(lua_State* L);
	glm::vec3* fill_vector3(lua_State* L);
	void addObject(std::string pProperties[2][2], glm::vec3 pVectors[3]);


	UserInterface* _gameHud;
	sf::RenderWindow* _window;
	Puzzle* _puzzle;
	RenderToTexture* _renderToTexture;
	World* _roomWorld;
	TPerson* _game;
	Light* light;
	GameObject* _roomParent;
	AbstractMaterial* _blackMaterial;
	GameObject* _aliud;
	GameObject* _shadowPlane;

	int _levelIndex = 1;
	bool _active = false;
	bool _paused = false;
	bool _aliudostium = false;
	float _pauseTimer = 0;
	float _aliudTimer = 0;

	bool _poloroidReversed = false;
	bool _menuReversed = true;

	bool _playingMenuAnimation = false;
	bool _playingMenuAnimationReversed = false;

	bool endMenuAnimation();
};

#endif

