#ifndef __PROJECTILE_H_
#define __PROJECTILE_H_

#include "Window.h"
#include "AABB.h"

#include <vector>

class Projectile
{
public:
	Projectile(Window * window, glm::vec3 pos, int damage, int speed, int size, int dir);
	void update();
	void maxSpeed();
	int getDamage();
	void setDamage(int damage);
	int getSpeed();
	void setSpeed(int speed);
	int getSize();
	void setSize(int size);
	AABB * getHitbox();
	glm::vec3 getVelocity();
	glm::vec3 getPosition();
	void setVelocity(glm::vec3 velocity);
	void setPosition(glm::vec3 position);
	bool getFired();
	void setFired(bool fired);
	int getDir();
	std::vector<int> hit;
private:
	const uint8 SPEED = 84;
	Window * window;
	int damage;
	int speed;
	int size;
	int dir;
	bool fired;
	glm::vec3 velocity;
	glm::vec3 position;
	AABB * hitbox;
};

#endif