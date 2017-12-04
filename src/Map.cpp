#include <iostream>
#include <math.h>

#include <fstream>
#include <Windows.h>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/norm.hpp>

#include "AABB.h"

#include "Map.h"

int lastMove = 0;
int xSelect = 0;
int ySelect = 0;

extern double deltaTime;

Map::Map(Window * window, Camera * camera, uint16 width, uint16 height) {
	this->camera = camera;
	this->window = window;
	this->width = width;
	this->height = height;
	map = new uint16[width * height];
	fmap = new uint16[width * height];
	tiles[0] = new Tile(camera, "res/textures/sky_tile.png", false, 0, DIMS, DIMS);
	tiles[1] = new Tile(camera, "res/textures/stone_tile_simple.png", true, 0, DIMS, DIMS);
	tiles[2] = new Tile(camera, "res/textures/campfire_simple.png", true, 0, DIMS, DIMS);
	tiles[3] = new Tile(camera, "res/textures/blank_tile.png", false, 0, DIMS, DIMS);
	tiles[4] = new Tile(camera, "res/textures/cracked_tile_simple.png", true, 0, DIMS, DIMS);
	for (uint16 k = 0; k < width; k++)
		for (uint16 l = 0; l < height; l++)
			fmap[k * height + l] = 3;
	for (uint16 i = 0; i < width; i++)
		for (uint16 j = 0; j < height; j++)
		{
			if (j == height-1 || j == 0 || i == 0 || i == width - 1)
				map[i * height + j] = 1;
			else
				map[i * height + j] = 0;
		}
	fmap[width / 2 * height + height / 2] = 2;
	fmap[4 * height + 4] = 4;
	std::vector<const char*> playerPaths
	{
		"res/textures/clatab_simple_down.png",
		"res/textures/clatab_simple_up.png",
		"res/textures/clatab_simple_left.png",
		"res/textures/clatab_simple_right.png",
		"res/textures/clatab_attack_simple.png"
	};
	player = new Player(window, camera, playerPaths);	
	selector = new TexRect(camera, "res/textures/selector.png", 16, 16, 0, DIMS, DIMS);

	zombies = std::vector<Zombie *>(0);
	items = std::vector<Item *>(0);

	std::vector<const char*> bubblePaths
	{
		"res/textures/bubble_left.png",
		"res/textures/bubble_up.png",
		"res/textures/bubble_right.png",
		"res/textures/bubble_down.png",
	};

	zombiePaths =
	{
		"res/textures/zombie_simple.png",
		"res/textures/zombie_simple_hurt.png"
	};

	bubble = new MultiRect(camera, bubblePaths, 0, 0, 0, 8, 2.5);
	bone = new TexRect(camera, "res/textures/bone.png", 0, 0, 0, 4+(1/3), 10);

	//WARNING LARGE BAD
	//L A R G E
	blank = new TexRect(camera, "res/textures/blank_tile.png", 0, 0, 0, 0, 0);

	selector->setPosition(roundUp(player->getPosition().x - 16, 16), roundUp(player->getPosition().y, 16));
	separation = 1;
}

void Map::update() {


		//separation = roundUp(abs(player->getPosition().x - selector->getPosition().x), 16);

		//camera->setPos(glm::vec3(player->getX() - camera->getWidth()/2, player->getY() - camera->getHeight() / 2, 0));

		if (window->isKeyPressed(GLFW_KEY_SPACE))
		{
			int tile = fmap[((int)selector->getPosition().x / 16) * height + (int)selector->getPosition().y / 16];
			if (player->getHolding() == -1 && tile != 3)
			{
				player->setHolding(tile);
				fmap[((int)selector->getPosition().x / 16) * height + (int)selector->getPosition().y / 16] = 3;
			}
		}
		if (window->isKeyPressed(GLFW_KEY_B))
		{
			if (player->getHolding() != -1)
			{
				fmap[((int)selector->getPosition().x / 16) * height + (int)selector->getPosition().y / 16] = player->getHolding();
				player->setHolding(-1);
			}
		}

		//player->setDistance(zombies.at(0)->getDistance());

		player->update();

		player->bulletCheck(width * DIMS, height * DIMS);

		for (size_t i = 0; i < zombies.size(); i++)
		{
			zombies[i]->update(player->getPosition());

			/*for (size_t k = 0; k < zombies.size(); k++)
				if (zombies[i]->getHitbox()->collides(zombies[k]->getHitbox()))
				{
					//zombies[i]->setVelocity(glm::vec3(5, 5, 0));
					//zombies[k]->setVelocity(glm::vec3(5, 5, 0));
					glm::vec3 pos1 = zombies[i]->getPosition();
					glm::vec3 pos2 = zombies[k]->getPosition();
					int dir = 0;
					if (pos1.x < pos2.x)
						dir = 0; //left
					else
						dir = 2; //right

					if (pos1.y < pos2.y)
						dir = 1; //up
					else
						dir = 3; //down

					float distanceX = abs((player->getPosition().x - zombies[i]->getPosition().x) / 200);
					float distanceY = abs((player->getPosition().y - zombies[i]->getPosition().y) / 200);

					switch (dir)
					{
					case 0:
						zombies[i]->setPosition(zombies[i]->getPosition().x - distanceX, zombies[i]->getPosition().y);
						break;
					case 1:
						zombies[i]->setPosition(zombies[i]->getPosition().x, zombies[i]->getPosition().y - distanceY);
						break;
					case 2:
						zombies[i]->setPosition(zombies[i]->getPosition().x + distanceX, zombies[i]->getPosition().y);
						break;
					case 3:
						zombies[i]->setPosition(zombies[i]->getPosition().x, zombies[i]->getPosition().y + distanceY);
						break;
					default:
						zombies[i]->setPosition(zombies[i]->getPosition().x - distanceX, zombies[i]->getPosition().y);
					}
				}*/

			if (player->getHitbox()->collides(zombies[i]->getHitbox()))
				player->setHealth(player->getHealth() - 1);

			for (int j = 0; j < player->getProjectiles().size(); j++)
				if (zombies.size() > 0)
					if (i < zombies.size())
						if (zombies[i > 0 ? i - 1 : 0]->getHitbox()->collides(player->getProjectiles()[j]->getHitbox()))
							if (zombies[i > 0 ? i - 1 : 0]->getHealth() <= 0)
							{
								items.push_back(new Item(zombies[i > 0 ? i - 1 : 0]->dropLoc()));
								zombies.erase(i > 0 ? zombies.begin() + i - 1 : zombies.begin());
								//items.at(items.size() - 1)->setPosition(glm::vec3(rand() % 200, rand() % 100, 0));
							}
							else
							{
								zombies[i > 0 ? i - 1 : 0]->state = 0;
								//if (!(std::find(player->getProjectiles()[j]->hit.begin(), player->getProjectiles()[j]->hit.end(), j) != player->getProjectiles()[j]->hit.end()))
								//{
								zombies[i > 0 ? i - 1 : 0]->setHealth(zombies[i > 0 ? i - 1 : 0]->getHealth() - 1);
								zombies[i > 0 ? i - 1 : 0]->state = 1;
								//player->getProjectiles()[j]->hit.emplace_back(i);
							//}
							}
		}

		if (player->getHealth() > 0)
		{
			if (lastMove > 5)
			{
				if (window->isKeyPressed(GLFW_KEY_RIGHT) && !window->isKeyPressed(GLFW_KEY_LEFT)) {
					selector->setPosition(selector->getPosition().x + 16, selector->getPosition().y);
					lastMove = 0;

				}
				if (window->isKeyPressed(GLFW_KEY_LEFT) && !window->isKeyPressed(GLFW_KEY_RIGHT)) {
					selector->setPosition(selector->getPosition().x - 16, selector->getPosition().y);
					lastMove = 0;

				}
				if (window->isKeyPressed(GLFW_KEY_UP) && !window->isKeyPressed(GLFW_KEY_DOWN)) {
					selector->setPosition(selector->getPosition().x, selector->getPosition().y - 16);
					lastMove = 0;

				}
				if (window->isKeyPressed(GLFW_KEY_DOWN) && !window->isKeyPressed(GLFW_KEY_UP)) {
					selector->setPosition(selector->getPosition().x, selector->getPosition().y + 16);
					lastMove = 0;
				}
				if (selector->getPosition().x / 16 > width - 1)
					selector->setPosition(selector->getPosition().x - 16, selector->getPosition().y);
				else if (selector->getPosition().x / 16 < 0)
					selector->setPosition(selector->getPosition().x + 16, selector->getPosition().y);
				if (selector->getPosition().y / 16 > height - 1)
					selector->setPosition(selector->getPosition().x, selector->getPosition().y - 16);
				else if (selector->getPosition().y / 16 < 0)
					selector->setPosition(selector->getPosition().x, selector->getPosition().y + 16);
			}
			else
				lastMove++;
		}

		float playerX = player->getPosition().x / 16;
		float playerY = player->getPosition().y / 16;
		float selectX = selector->getPosition().x / 16;
		float selectY = selector->getPosition().y / 16;

		separation = (sqrt(pow(selectX - playerX, 2) + pow(selectY - playerY, 2)));

		for (auto i = 0; i < items.size(); i++)
		{
			items[i]->update();
			if (player->getHitbox()->collides(items[i]->getHitbox()))
			{
				items.erase(items.begin() + i);
				player->bones++;
			}
		}

		std::cout << zombies.size() << std::endl;

		//camera->setPos(glm::vec3(player->getX(), player->getY(), 0));
		while (checkCollision(0, 0));
		for (size_t i = 0; i < zombies.size(); i++)
		{
			while (checkCollision(1, i));
		}

		if (window->isKeyPressed(GLFW_KEY_Z))
			spawnZombies(1);
		//std::cout << player->getHitbox()->getPosition().x << ", " << player->getHitbox()->getPosition().y << std::endl;
}

void Map::spawnZombies(int num)
{
	zombies.push_back(new Zombie(window, camera, zombiePaths, 10));
	zombies.at(zombies.size()-1)->setPosition(glm::vec3(rand() % 200, rand() % 100, 0));
}

void Map::spawnWave(int wave)
{
	if (wave < 3)
	{
		switch (wave)
		{
		case 0:
			zombies.push_back(new Zombie(window, camera, zombiePaths, 10));
			zombies.at(zombies.size() - 1)->setPosition(glm::vec3(10 * 16, 1 * 16, 0));
			break;
		case 1:
			for (int i = 0; i < 5; i++)
			{
				zombies.push_back(new Zombie(window, camera, zombiePaths, 10));
				zombies.at(zombies.size() - 1)->setPosition(glm::vec3(i * 16, 1 * 16, 0));
			}
			break;
		case 2:
			for (int i = 0; i < 10; i++)
			{
				zombies.push_back(new Zombie(window, camera, zombiePaths, 10));
				zombies.at(zombies.size() - 1)->setPosition(glm::vec3(i * 16, 1 * 16, 0));
			}
			break;
		case 3:
			for (int i = 0; i < 16; i++)
			{
				zombies.push_back(new Zombie(window, camera, zombiePaths, 10));
				zombies.at(zombies.size() - 1)->setPosition(glm::vec3(i * 16, 1 * 16, 0));
			}
			break;
		}
	} 
	else
	{
		for (int i = 0; i < wave * 5; i++)
		{
			zombies.push_back(new Zombie(window, camera, zombiePaths, 10));
			zombies.at(zombies.size() - 1)->setPosition(pickPos());
		}
	}
}

glm::vec3 Map::pickPos()
{
	float spots = camera->getWidth() / 16;
	int side = 0 + (rand() % static_cast<int>(3 - 0 + 1));
	int xSpot = 1 + (rand() % static_cast<int>((camera->getWidth()-16 / 16) - 1 + 1));
	int ySpot = 1 + (rand() % static_cast<int>((camera->getHeight()-16 / 16) - 1 + 1));
	switch (side)
	{
	case 0:
		return glm::vec3(xSpot*16, 8, 0);
		break;
	case 1:
		return glm::vec3(xSpot*16, camera->getHeight() - 16 , 0);
		break;
	case 2:
		return glm::vec3(8, ySpot*16, 0);
		break;
	case 3:
		return glm::vec3(camera->getWidth() - 16 , ySpot*16, 0);
		break;
	}
	return glm::vec3(xSpot, 0, 0);
}

void Map::spawnBlock(int type)
{
	switch (type)
	{
	case 1:
		fmap[1 * height + 1] = 4;
		break;
	case 2:
		fmap[1 * height + 1] = 2;
		break;
	case 3:
		fmap[1 * height + 1] = 2;
		break;
	} 
}

bool Map::checkCollision(int type, int za) {
	//players
	if (type == 0)
	{
		AABB * playerHit = player->getHitbox();
		AABB * closest = 0;
		AABB * current = 0;
		glm::vec3 closestLength;
		int minX = floor(player->getX() / DIMS);
		int maxX = ceil(player->getX() / DIMS);
		int minY = floor(player->getY() / DIMS);
		int maxY = ceil(player->getY() / DIMS);
		if (minX >= 0 && maxX < width && minY >= 0 && maxY < height) {
			for (uint8 i = minX; i <= maxX; ++i) {
				for (uint8 j = minY; j <= maxY; ++j) {
					Tile * curTile = tiles[map[i * height + j]];
					if (fmap[i * height + j] != 3)
						curTile = tiles[fmap[i * height + j]];
					if (curTile->isSolid()) {
						if (!closest) {
							closest = new AABB(i * DIMS, j * DIMS, DIMS, DIMS);
							closestLength = closest->getCenter() + (-playerHit->getCenter());
						}
						else {
							if (current)
								delete current;
							current = new AABB(i * DIMS, j * DIMS, DIMS, DIMS);
							glm::vec3 curLength = current->getCenter() + (-playerHit->getCenter());
							if (glm::length2(curLength) < glm::length2(closestLength)) {
								closestLength = curLength;
								delete closest;
								closest = current;
								current = 0;
							}
						}
					}
				}
			}
		}
		bool ret = false;
		if (closest) {
			if (closest->collides(playerHit)) {
				glm::vec3 transform = closest->getTransform(playerHit);
				if ((player->getVelocity().y < 0 && transform.y < 0) || (player->getVelocity().y > 0 && transform.y > 0)) {
					transform.x = closest->getTransformX(playerHit);
					transform.y = 0;
				}
				else if ((player->getVelocity().x < 0 && transform.x < 0) || (player->getVelocity().x > 0 && transform.x > 0)) {
					transform.y = closest->getTransformY(playerHit);
					transform.x = 0;
				}
				player->translate(transform);
				player->alignHitbox();
				if (transform.y < 0)
					player->hitBottom();
				else if (transform.x > 0)
					player->hitLeft();
				else if (transform.x < 0)
					player->hitRight();
				else
					player->hitTop();
				ret = true;
			}
			if (current)
				delete current;
			delete closest;
		}
		return ret;
		//zombies
	}
	else if (type == 1) 
	{
			AABB * playerHit = zombies[za]->getHitbox();
			AABB * closest = 0;
			AABB * current = 0;
			glm::vec3 closestLength;
			int minX = floor(zombies[za]->getX() / DIMS);
			int maxX = ceil(zombies[za]->getX() / DIMS);
			int minY = floor(zombies[za]->getY() / DIMS);
			int maxY = ceil(zombies[za]->getY() / DIMS);
			if (minX >= 0 && maxX < width && minY >= 0 && maxY < height) {
				for (uint8 i = minX; i <= maxX; ++i) {
					for (uint8 j = minY; j <= maxY; ++j) {
						Tile * curTile = tiles[map[i * height + j]];
						if (fmap[i * height + j] != 3)
							curTile = tiles[fmap[i * height + j]];
						if (curTile->isSolid()) {
							if (!closest) {
								closest = new AABB(i * DIMS, j * DIMS, DIMS, DIMS);
								closestLength = closest->getCenter() + (-playerHit->getCenter());
							}
							else {
								if (current)
									delete current;
								current = new AABB(i * DIMS, j * DIMS, DIMS, DIMS);
								glm::vec3 curLength = current->getCenter() + (-playerHit->getCenter());
								if (glm::length2(curLength) < glm::length2(closestLength)) {
									closestLength = curLength;
									delete closest;
									closest = current;
									current = 0;
								}
							}
						}
					}
				}
			}
			bool ret = false;
			if (closest) {
				if (closest->collides(playerHit)) {
					glm::vec3 transform = closest->getTransform(playerHit);
					if ((zombies[za]->getVelocity().y < 0 && transform.y < 0) || (zombies[za]->getVelocity().y > 0 && transform.y > 0)) {
						transform.x = closest->getTransformX(playerHit);
						transform.y = 0;
					}
					else if ((zombies[za]->getVelocity().x < 0 && transform.x < 0) || (zombies[za]->getVelocity().x > 0 && transform.x > 0)) {
						transform.y = closest->getTransformY(playerHit);
						transform.x = 0;
					}
					zombies[za]->translate(transform);
					//std::cout << za << std::endl;
					zombies[za]->alignHitbox();
					if (transform.y < 0)
						zombies[za]->hitBottom();
					else if (transform.x > 0)
						zombies[za]->hitLeft();
					else if (transform.x < 0)
						zombies[za]->hitRight();
					else
						zombies[za]->hitTop();
					ret = true;
				}
				if (current)
					delete current;
				delete closest;
			}
			return ret;
		
	}
}

void Map::render() {
	for (auto i = 0; i < player->getProjectiles().size(); i++)
	{
		bubble->setPosition(player->getProjectiles()[i]->getPosition());
		auto dir = player->getProjectiles()[i]->getDir();
		if (dir == 1 || dir == 3)
		{
			bubble->setWidth(2.5);
			bubble->setHeight(8);
		}
		else
		{
			bubble->setWidth(8);
			bubble->setHeight(2.5);
		}
		bubble->render(player->getProjectiles()[i]->getDir());
	}

	for (auto i = 0; i < items.size(); i++)
	{
		bone->setPosition(items[i]->getPosition());
		bone->render();
	}

	tiles[player->getHolding()]->setWidth(32);
	tiles[player->getHolding()]->setHeight(32);
	tiles[player->getHolding()]->setPosition(camera->getWidth() - 36, 4);
	tiles[player->getHolding()]->render();
	tiles[player->getHolding()]->setWidth(16);
	tiles[player->getHolding()]->setHeight(16);

	selector->render();
	for (size_t i = 0; i < zombies.size(); i++)
	{
		//zombies[i]->healthBar->render();
		zombies[i]->render(zombies[i]->state);
		//zombies[i]->shadow->render();
	}
	/*int minX = fmax(camera->getPos().x / DIMS, 0);
	int maxX = fmin((camera->getPos().x + camera->getWidth()) / DIMS, width);
	int minY = fmax(camera->getPos().y / DIMS, 0);
	int maxY = fmin((camera->getPos().y + camera->getHeight()) / DIMS, height);*/
	for (uint16 i = 0; i < width; ++i) {
		for (uint16 j = 0; j < height; ++j) 
		{
			tiles[fmap[i * height + j]]->setPosition(i * DIMS, j * DIMS);
			tiles[fmap[i * height + j]]->render();
			player->render(player->state);
			tiles[map[i * height + j]]->setPosition(i * DIMS, j * DIMS);
			tiles[map[i * height + j]]->render();
		}
	}
}

void Map::setSeparation(int separation)
{
	this->separation = separation;
}

int Map::getSelectorX()
{
	return selector->getPosition().x;
}

int Map::getSelectorY()
{
	return selector->getPosition().y;
}

Player * Map::getPlayer()
{
	return player;
}

int Map::roundUp(int numToRound, int multiple)
{
	if (multiple == 0)
		return numToRound;

	int remainder = numToRound % multiple;
	if (remainder == 0)
		return numToRound;

	return numToRound + multiple - remainder;
}


Map::~Map() {
	delete [] map;
	for (uint16 i = 0; i < NUM_TILES; ++i)
		delete tiles[i];
}