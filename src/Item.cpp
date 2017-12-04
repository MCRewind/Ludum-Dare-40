#include "Item.h"

#include <iostream>

Item::Item(glm::vec3 pos)
{
	position = pos;
	hitbox = new AABB(position.x, position.y, 4 + (1 / 3), 10);
	startY = position.y;
	bobSlice = .08;
	down = false;
	lock = false;
}

void Item::update()
{
	if (down)
	{
		position.y += bobSlice;
		lock = true;
		if (position.y >= startY)
		{
			down = false;
			lock = false;
		}
	}
	if (position.y >= startY - 3)
	{
		if (!lock)
		{
			position.y -= bobSlice;
			down = false;
		}
	}
	else
	{
		down = true;
	}

	hitbox->setPosition(position);
}

AABB * Item::getHitbox()
{
	return hitbox;
}

glm::vec3 Item::getPosition()
{
	return position;
}

void Item::setPosition(glm::vec3 position)
{
	this->position = position;
}