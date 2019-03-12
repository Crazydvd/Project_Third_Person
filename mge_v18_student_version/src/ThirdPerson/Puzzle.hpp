#ifndef PUZZLE_HPP
#define PUZZLE_HPP

#include <string>
#include <glm/glm.hpp>
#include <lua.hpp>
#include "SFML/Graphics/RenderWindow.hpp"
#include <mge/core/GameObject.hpp>
#include "ThirdPerson/Timer.hpp"
#include "ThirdPerson/UITexture.hpp"
#include "ThirdPerson/UserInterface.hpp"

//class GameObject;
class RenderWindow;
class World;

class Puzzle : public GameObject
{
	public:
		Puzzle(sf::RenderWindow* pWindow, World* pWorld, int plevelIndex, std::string pName = "puzzle", glm::vec3 pPosition = glm::vec3(0,0,0));

		virtual ~Puzzle();
		virtual void update(float pStep);
		void draw();
		std::vector<GameObject*> getObjects();

		Timer* PuzzleTimer;
		bool Paused = false;

	private:
		void loadObject(std::string pName, std::string pProperties[2][2], glm::vec3 pVectors[3]);
		void getPuzzles(lua_State* L, std::string name = "gameobject");
		glm::vec3* fill_vector3(lua_State* L);
		void loadScoreTimes(lua_State* L);
		void loadLetter(lua_State* L);
		void checkOnePuzzle();
		void rotateWithKeys();

		World* _world;
		std::vector<GameObject*> _puzzleObjects;
		sf::RenderWindow* _window;
		UserInterface* _popups;
		bool _started = false;
		bool _tutorial = false;
		bool _completed = false;
		int _levelIndex;
		int _victoryDelay;
		float _tripleStarTime = 30.0f;
		float _doubleStarTime = 60.0f;

};

#endif // !PUZZLE_HPP

