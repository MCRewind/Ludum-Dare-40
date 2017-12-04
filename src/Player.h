#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "Window.h"
#include "Rect.h"
#include "AABB.h"
#include "Projectile.h"

#include <vector>

class Player : public MultiRect
{
public:
	Player(Window * window, Camera * camera, std::vector<const char*> paths);
	void update();
	AABB * getHitbox();
	glm::vec3 getVelocity();
	void alignHitbox();
	void hitTop();
	void hitLeft();
	void hitRight();
	void hitBottom();
	void setGravity(float gravity);
	void setDistance(float distance);
	int getHealth();
	void setHealth(int health);
	int getHolding();
	void setHolding(int id);
	void attack();
	void spawnProjectile(int dir);
	std::vector<Projectile *> getProjectiles();
	void bulletCheck(int width, int height);
	int state = 0;
	int bones;
	~Player();
private:
	std::vector<Projectile *> projectiles;
	const uint8 SPEED = 64;
	Window * window;
	AABB * hitbox;
	bool grounded = true, jump = false;
	uint16 space = 0;
	float gravity;
	glm::vec3 velocity;
	int health;
	int holding;
	int roundUp(int numToRound, int multiple);
	
};

#endif