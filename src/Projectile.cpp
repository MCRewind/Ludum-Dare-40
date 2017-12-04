#include "Projectile.h"

extern double deltaTime;
bool fired;

Projectile::Projectile(Window * window, glm::vec3 pos, int damage, int speed, int size, int dir)
{
	this->window = window;
	this->damage = damage;
	this->speed = speed;
	this->size = size;
	this->dir = dir;
	position = pos;
	hitbox = new AABB(position.x, position.y, 8, 8);
}

void Projectile::update()
{
	if (!fired)
	{
		velocity.y = 0;
		velocity.x = 0;
	}

	position += (velocity * (float)deltaTime);
	hitbox->setPosition(position);
}

void Projectile::maxSpeed()
{
	switch (dir)
	{
	case 0:
		velocity.x = -SPEED;
		break;
	case 1:
		velocity.y = -SPEED;
		break;
	case 2:
		velocity.x = SPEED;
		break;
	case 3:
		velocity.y = SPEED;
		break;
	default:
		velocity.x = SPEED;
	}
	fired = true;
}

int Projectile::getDamage()
{
	return damage;
}

void Projectile::setDamage(int damage)
{
	this->damage = damage;
}

int Projectile::getSpeed()
{
	return speed;
}

void Projectile::setSpeed(int speed)
{
	this->speed = speed;
}

int Projectile::getSize()
{
	return size;
}

void Projectile::setSize(int size)
{
	this->size = size;
}

AABB * Projectile::getHitbox() {
	return hitbox;
}

glm::vec3 Projectile::getVelocity() {
	return velocity;
}

void Projectile::setVelocity(glm::vec3 velocity)
{
	this->velocity = velocity;
}

glm::vec3 Projectile::getPosition() {
	return position;
}

void Projectile::setPosition(glm::vec3 position)
{
	this->velocity = velocity;
}

bool Projectile::getFired()
{
	return fired;
}

void Projectile::setFired(bool fired)
{
	this->fired = fired;
}

int Projectile::getDir()
{
	return dir;
}