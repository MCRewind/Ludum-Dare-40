#ifndef MAP
#define MAP

#include "Types.h"
#include "Window.h"
#include "Camera.h"
#include "Player.h"
#include "Zombie.h"
#include "Tile.h"
#include "Item.h"

#include <vector>

class Map {
	public:
		Map(Window * window, Camera * camera, uint16 width, uint16 height);
		void update();
		bool checkCollision(int type, int za);
		void render();
		Player * getPlayer();
		void spawnBlock(int type);
		glm::vec3 pickPos();
		std::vector<Zombie *> zombies;
		std::vector<Item *> items;
		std::vector<const char*> zombiePaths;
		void spawnWave(int wave);
		~Map();
	private:
		const static uint16 NUM_TILES = 5;
		const uint8 DIMS = 16;
		Camera * camera;
		Window * window;
		Player * player;
		MultiRect * bubble;
		TexRect * blank;
		Tile * tiles[NUM_TILES];
		uint16 * map, width, height;
		uint16 * fmap;
		TexRect * selector, * bone;
		int roundUp(int numToRound, int multiple);
		void setSeparation(int separation);
		int separation;
		int getSelectorX();
		int getSelectorY();
		void spawnZombies(int num);
};

#endif