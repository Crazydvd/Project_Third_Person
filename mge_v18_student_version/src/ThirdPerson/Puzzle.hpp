#ifndef PUZZLE_HPP
#define PUZZLE_HPP

#include <string>
#include <glm/glm.hpp>
#include <lua.hpp>
#include "SFML/Graphics/RenderWindow.hpp"
#include <mge/core/GameObject.hpp>
#include "ThirdPerson/Timer.hpp"

//class GameObject;
class RenderWindow;
class World;

class Puzzle : public GameObject
{
	public:
		Puzzle(sf::RenderWindow* pWindow, World* pWorld, int plevelIndex, std::string pName = "puzzle", glm::vec3 pPosition = glm::vec3(0,0,0));

		virtual ~Puzzle();
		virtual void update(float pStep);
		std::vector<GameObject*> getObjects();

		Timer* PuzzleTimer;
		bool Paused = false;

	private:
		void loadObject(std::string pProperties[2][2], glm::vec3 pVectors[2]);
		void getPuzzles(lua_State* L);
		glm::vec3* fill_vector3(lua_State* L);
		void checkOnePuzzle();
		void checkMultiplePuzzles();
		void rotateWithKeys();

		bool _inTolereance = false;
		bool _completed = false;
		int _levelIndex;
		int _victoryDelay = 0;
		World* _world;
		std::vector<GameObject*> _puzzleObjects;
		sf::RenderWindow* _window;
};

#endif // !PUZZLE_HPP

