#include <iostream>

#include "Player.h"

extern double deltaTime;

int attackTime = 21;
int shootTime = 11;
int lastDir = 0;
int lastState = 0;

Player::Player(Window * window, Camera* camera, std::vector<const char*> paths) : MultiRect(camera, paths, 20, 20, 0, 16, 16)
{
	this->window = window;
	gravity = 25.0f;
	hitbox = new AABB(position.x, position.y, 16, 16);
	health = 150;
	holding = -1;
	bones = 0;
}

void Player::update() {
	bool direction = false;
	if (health > 0)
	{
		if (window->isKeyPressed(GLFW_KEY_D) && !window->isKeyPressed(GLFW_KEY_A)) {
			velocity.x = SPEED;
			direction = true;
			lastDir = 2;
			lastState = 3;
		}
		if (window->isKeyPressed(GLFW_KEY_A) && !window->isKeyPressed(GLFW_KEY_D)) {
			velocity.x = -SPEED;
			direction = true;
			lastDir = 0;
			lastState = 2;
		}
		if (window->isKeyPressed(GLFW_KEY_W) && !window->isKeyPressed(GLFW_KEY_S)) {
			velocity.y = -SPEED;
			direction = true;
			lastDir = 1;
			lastState = 1;
		}
		if (window->isKeyPressed(GLFW_KEY_S) && !window->isKeyPressed(GLFW_KEY_W)) {
			velocity.y = SPEED;
			direction = true;
			lastDir = 3;
			lastState = 0;
		}

		state = lastState;

		if (window->isKeyPressed(GLFW_KEY_J))
			spawnProjectile(lastDir);

		if (window->isKeyPressed(GLFW_KEY_H))
			attack();
	}

	else if (projectiles.size() > 0)
		projectiles.front()->setFired(false);

	

	for (auto i = 0; i < projectiles.size(); i++)
	{
		projectiles[i]->maxSpeed();
		projectiles[i]->update();
	}

	attackTime > 100 ? attackTime = 100 : attackTime++;
	shootTime > 100 ? shootTime = 100 : shootTime++;

	if (state == 4)
	{
		if (attackTime == 20)
			state = lastState;
	}
	

	if (!direction)
	{
		velocity.y = 0;
		velocity.x = 0;
	}

	//velocity.y += gravity;
	position += (velocity * (float)deltaTime);
	hitbox->setPosition(position);
}

void Player::spawnProjectile(int dir)
{
	if (shootTime > 20)
	{
		projectiles.emplace_back(new Projectile(window, position, 10, 5, 8, dir));
		std::cout << projectiles.size() << std::endl;
		shootTime = 0;
	}
}

void Player::attack()
{
	if (attackTime > 20)
	{
		state = 4;
		attackTime = 0;
	}
	
}

void Player::bulletCheck(int width, int height)
{
	for (auto i = 0; i < projectiles.size(); i++)
		if (projectiles[i]->getPosition().x > width || projectiles[i]->getPosition().x + 8 < 0 ||
			projectiles[i]->getPosition().y > height || projectiles[i]->getPosition().y + 8 < 0)
			projectiles.erase(projectiles.begin() + (i > 0 ? i - 1 : 0));
}

int Player::roundUp(int numToRound, int multiple)
{
	if (multiple == 0)
		return numToRound;

	int remainder = numToRound % multiple;
	if (remainder == 0)
		return numToRound;

	return numToRound + multiple - remainder;
}

AABB * Player::getHitbox() {
	return hitbox;
}

glm::vec3 Player::getVelocity() {
	return velocity;
}

void Player::alignHitbox() {
	hitbox->setPosition(position);
}

void Player::hitBottom() {
	velocity.y = 0;
	grounded = true;
}

void Player::hitLeft() {
	velocity.x = 0;
}

void Player::hitRight() {
	velocity.x = 0;
}

void Player::hitTop()
{
	velocity.y = 0;
}

void Player::setDistance(float distance)
{
	
	getShader()->setDistance(abs(1/(distance + 1)));
	//std::cout << abs(1 / (distance + 1)) << std::endl;
}

int Player::getHealth()
{
	return health;
}

void Player::setHealth(int health) 
{
	this->health = health;
}

int Player::getHolding()
{
	return holding;
}

void Player::setHolding(int id)
{
	this->holding = id;
}

std::vector<Projectile *> Player::getProjectiles()
{
	return projectiles;
}

Player::~Player() 
{
	delete hitbox;
}