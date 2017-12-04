#include "AABBUtils.h"
#include <iostream>

/*bool checkCollisions(int map[5][5], AABB* hitbox, float &x, float &y)
{
	int left_tile = floor(x / 16) < 0 ? 0 : (floor(x / 16) > 5 ? 5 : floor(x / 16));
	int right_tile = ceil(((x + 16) / 16)) < 0 ? 0 : ceil(((x + 16) / 16)) > 5 ? 5 : ceil(((x + 16) / 16));
	int top_tile = floor(y / 16) < 0 ? 0 : (floor(y / 16) > 5 ? 5 : floor(y / 16));
	int bottom_tile = ceil(((y + 16) / 16)) < 0 ? 0 : ceil(((y + 16) / 16)) > 5 ? 5 : ceil(((y + 16) / 16));

	//std::cout << left_tile << ", " << right_tile << ", " << top_tile << ", " << bottom_tile << std::endl;

	for (int i = left_tile; i <= right_tile; i++)
		for (int j = top_tile; j < bottom_tile; j++)
		{
			if (map[i][j] == 1)
			{
				AABB other(i * 16, j * 16, 16, 16);

//				if (hitbox->overlaps(other))
	//			{
					//int dx = (hitbox->center.x) - (other->center.x);
					//int dy = (hitbox->center.y) - (other->center.y);
					int dx = abs(hitbox->center.x - hitbox->center.x) - abs(other.getPos().x + hitbox->halfSize.x);
					int dy = abs(hitbox->center.x - hitbox->center.y) - abs(hitbox->halfSize.y + hitbox->halfSize.y);
					std::cout << hitbox->center.x << std::endl;
					//std::cout << "colliding" << std::endl;
					(abs(dx) > abs(dy) ? dx : dy) = 0;
					if (dx && hitbox->center.x < hitbox->center.x) dx = -dx;
					else if (hitbox->center.y < hitbox->center.y) dy = -dy;
					y += dy;
					x += dx;
					return true;
			//	}
			}
		}
	return false;
}*/