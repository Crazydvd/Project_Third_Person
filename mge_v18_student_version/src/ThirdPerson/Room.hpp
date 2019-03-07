#ifndef ROOM_HPP
#define ROOM_HPP

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <lua.hpp>
#include "glm.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Light.hpp"
#include "ThirdPerson/Timer.hpp"
#include "ThirdPerson/Puzzle.hpp"

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

private:
	void print_table(lua_State* L);
	glm::vec3* fill_vector3(lua_State* L);
	void addObject(std::string pProperties[2][2], glm::vec3 pVectors[3]);
	void Initialize(int levelIndex);

	void MoveToNextLevel();
	void MoveToPreviousLevel();

	sf::RenderWindow* _window;
	Puzzle* _puzzle;
	RenderToTexture* _renderToTexture;
	World* _roomWorld;
	TPerson* _game;
	Light* light;
	GameObject* _roomParent;
	int _levelIndex = 1;
	AbstractMaterial* _blackMaterial;
};

#endif

