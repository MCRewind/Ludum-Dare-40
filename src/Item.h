#ifndef __ITEM_H_
#define __ITEM_H_

#include "AABB.h"

class Item
{
public:
	Item(glm::vec3 pos);
	void update();
	AABB * getHitbox();
	glm::vec3 getPosition();
	void setPosition(glm::vec3 position);
private:
	AABB * hitbox;
	glm::vec3 position;
	double startY, bobSlice;
	bool down, lock;
};

#endif