#include "Zombie.h"

extern double deltaTime;

Zombie::Zombie(Window * window, Camera* camera, std::vector<const char*> paths, int health) : MultiRect(camera, paths, 32, 32, 0, 16, 16)
{
	this->window = window;
	hitbox = new AABB(position.x, position.y, 16, 16);
	distanceX = 1;
	distanceY = 1;
	this->health = health;
	shadow = new TexRect(camera, "res/textures/shadow.png", 32, 32, 0, 16, 4);
	healthBar = new ColRect(camera, 0, 1, 0, 1, position.x, position.y, 0, 6, 5);
	follow = true;
	state = 0;
}

void Zombie::update(glm::vec3 playerPos) {

	shadow->setPosition(position.x, position.y + height - 2);

	healthBar->setPosition(position.x, position.y);
	healthBar->setWidth(health);

	//int time = 1000 + (rand() % static_cast<int>(10000 - 1000 + 1));

	if (follow)
	{
		distanceX = playerPos.x - position.x;
		distanceY = playerPos.y - position.y;

		position.y += (distanceY / 200);
		position.x += (distanceX / 200);
	}
	//velocity.x -= (velocity.x > 0 ? 1 : 0);
	//velocity.y -= (velocity.y > 0 ? 1 : 0);

	position += (velocity * (float)deltaTime);
	hitbox->setPosition(position);
}

glm::vec3 Zombie::dropLoc()
{
	//TODO maybe drop bone
	return glm::vec3(position);
}

AABB * Zombie::getHitbox() {
	return hitbox;
}

glm::vec3 Zombie::getVelocity() {
	return velocity;
}

void Zombie::setVelocity(glm::vec3 vel) {
	this->velocity = vel;
}


void Zombie::alignHitbox() {
	hitbox->setPosition(position);
}

void Zombie::hitBottom() {
	velocity.y = 0;
	grounded = true;
}

void Zombie::hitLeft() {
	velocity.x = 0;
}

void Zombie::hitRight() {
	velocity.x = 0;
}

void Zombie::hitTop() {
	velocity.y = 0;
}

float Zombie::getDistance()
{
	return (distanceX + distanceY) / 2;
}

int Zombie::getHealth()
{
	return health;
}

void Zombie::setHealth(int health)
{
	this->health = health;
}