#include "GamePanel.h"

#include <string>

int keyOneState = 0;
int keyTwoState = 0;
int keyThreeState = 0;
int buyOneTime = 20;
int buyTwoTime = 20;
int buyThreeTime = 20;

GamePanel::GamePanel(Window * window, Camera * camera) : Panel(window, camera) {
	state = 0;
	this->window = window;
	this->camera = camera;
	map = new Map(window, camera, camera->getWidth() / 16, camera->getHeight() / 16);
	health = new ColRect(camera, 1, 0, 0, 1, camera->getWidth() / 2 - 75, camera->getHeight() - 10, 0, 50, 10);
	selected = new TexRect(camera, "res/textures/selected.png", camera->getWidth() - 40, 0, 0, 40, 40);
	death = new TexRect(camera, "res/textures/death.png", camera->getWidth() / 2 - 64, camera->getHeight() / 2 - 64, 0, 128, 128);
	boneSign = new TexRect(camera, "res/textures/boneSign.png", 60, 2, 0, 15, 10.5);
	waves = new TexRect(camera, "res/textures/waves.png", 110, 6, 0, 21.25, 3.75);

	std::vector<const char*> digitPaths =
	{
		"res/textures/0.png",
		"res/textures/1.png",
		"res/textures/2.png",
		"res/textures/3.png",
		"res/textures/4.png",
		"res/textures/5.png",
		"res/textures/6.png",
		"res/textures/7.png",
		"res/textures/8.png",
		"res/textures/9.png",
	};

	digitOne = new MultiRect(camera, digitPaths, 77, 4, 0, 6, 8);
	digitTwo = new MultiRect(camera, digitPaths, 87, 4, 0, 6, 8);
	digitThree = new MultiRect(camera, digitPaths, 97, 4, 0, 6, 8);
	waveCount = new MultiRect(camera, digitPaths, 130, 4, 0, 6, 8);

	std::vector<const char*> keyOnePaths =
	{
		"res/textures/keyOne.png",
		"res/textures/keyOnePressed.png"
	};

	std::vector<const char*> keyTwoPaths =
	{
		"res/textures/keyTwo.png",
		"res/textures/keyTwoPressed.png"
	};

	std::vector<const char*> keyThreePaths =
	{
		"res/textures/keyThree.png",
		"res/textures/keyThreePressed.png"
	};

	keyOne = new MultiRect(camera, keyOnePaths, 0, 0, 0, 16, 16);
	keyTwo = new MultiRect(camera, keyTwoPaths, 20, 0, 0, 16, 16);
	keyThree = new MultiRect(camera, keyThreePaths, 40, 0, 0, 16, 16);

	wave = 0;
	map->spawnWave(wave);
}

void GamePanel::update() {
	if (map->zombies.size() <= 0)
	{
		wave++;
		map->spawnWave(wave);
	}
	map->update();
	health->setWidth(map->getPlayer()->getHealth());

	if (window->isKeyPressed(GLFW_KEY_1))
		keyOnePress();
	else
		keyOneState = 0;

	if (window->isKeyPressed(GLFW_KEY_2))
		keyTwoPress();
	else
		keyTwoState = 0;

	if (window->isKeyPressed(GLFW_KEY_3))
		keyThreePress();
	else
		keyThreeState = 0;

	if (map->getPlayer()->getHealth() < 0)
		if (window->isKeyPressed(GLFW_KEY_X))
		{
			GamePanel(window, camera);
		}

	buyOneTime > 100 ? buyOneTime = 100 : buyOneTime++;
	buyTwoTime > 100 ? buyTwoTime = 100 : buyTwoTime++;
	buyThreeTime > 100 ? buyThreeTime = 100 : buyThreeTime++;

	/*if (window->isKeyPressed(GLFW_KEY_LEFT))
		camera->translate(glm::vec3(-3, 0, 0));
	if (window->isKeyPressed(GLFW_KEY_RIGHT))
		camera->translate(glm::vec3(3, 0, 0));
	if (window->isKeyPressed(GLFW_KEY_UP))
		camera->translate(glm::vec3(0, -3, 0));
	if (window->isKeyPressed(GLFW_KEY_DOWN))
		camera->translate(glm::vec3(0, 3, 0));
	if (window->isKeyPressed(GLFW_KEY_N))
		camera->zoomi();
	if (window->isKeyPressed(GLFW_KEY_M))
		camera->zoomo();*/
}

void GamePanel::keyOnePress()
{
	keyOneState = 1;
	if (buyOneTime > 20)
	{
		if (map->getPlayer()->bones >= 5)
		{
			map->spawnBlock(1);
			map->getPlayer()->bones -= 5;
			buyOneTime = 0;
		}
	}
}

void GamePanel::keyTwoPress()
{
	keyTwoState = 1;
	if (buyTwoTime > 20)
	{
		if (map->getPlayer()->bones >= 15)
		{
			map->spawnBlock(2);
			map->getPlayer()->bones -= 15;
			buyTwoTime = 0;
		}
	}
}

void GamePanel::keyThreePress()
{
	keyThreeState = 1;
	if (buyThreeTime > 20)
	{
		if (map->getPlayer()->bones >= 50)
		{
			map->spawnBlock(3);
			map->getPlayer()->bones -= 50;
			buyThreeTime = 0;
		}
	}
}

void GamePanel::render() {
	waveCount->render(wave);
	waves->render();
	boneSign->render();
	std::string s = std::to_string(map->getPlayer()->bones);
	if (s.size() > 0)
		digitOne->render(s.at(0) - '0');
	if (s.size() > 1)
		digitTwo->render(s.at(1) - '0');
	if (s.size() > 2)
		digitThree->render(s.at(2) - '0');
	keyOne->render(keyOneState);
	keyTwo->render(keyTwoState);
	keyThree->render(keyThreeState);
	if (map->getPlayer()->getHealth() < 0)
		death->render();
	selected->render();
	if (map->getPlayer()->getHealth() > 0)
		health->render();
	map->render();
}

void GamePanel::setActive()
{
	state = 0;
}

GamePanel::~GamePanel() {
	delete map;
}