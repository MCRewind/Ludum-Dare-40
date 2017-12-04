#ifndef __ZOMBIE_H_
#define __ZOMBIE_H_

#include "Window.h"

#include "Rect.h"

#include "AABB.h"

class Zombie : public MultiRect
{
public:
	Zombie(Window * window, Camera * camera, std::vector<const char*> paths, int health);
	void update(glm::vec3 playerPos);
	AABB * getHitbox();
	glm::vec3 getVelocity();
	void alignHitbox();
	void hitTop();
	void hitLeft();
	void hitRight();
	void hitBottom();
	float getDistance();
	int getHealth();
	void setVelocity(glm::vec3 vel);
	void setHealth(int health);
	glm::vec3 dropLoc();
	TexRect * shadow;
	ColRect * healthBar;
	int state;
private:
	int health;
	float distanceX, distanceY;
	const uint8 SPEED = 84,
		SPACE_HELD = 12,
		WALL_SLIDE = 25;
	Window * window;
	AABB * hitbox;
	bool grounded = true, jump = false;
	uint16 space = 0;
	float gravity;
	glm::vec3 velocity;
	bool follow;
};

#endif