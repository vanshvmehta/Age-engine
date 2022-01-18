#include "gravity.h"
#include "../entity/entity.h"

Gravity::Gravity(BorderDirection border) {
	if (border == BorderDirection::SOUTH) direction = std::vector<int> {0, 1, 0};
	else if (border == BorderDirection::NORTH) direction = std::vector<int> {0, -1, 0};
	else if (border == BorderDirection::EAST) direction = std::vector<int> {1, 0, 0};
	else if (border == BorderDirection::WEST) direction = std::vector<int> {-1, 0, 0};
}

void Gravity::move(Entity *entity) {
	std::vector<int> entityPos = entity->getPos();
	entityPos[0] += direction[0];
	entityPos[1] += direction[1];
	entityPos[2] += direction[2];

	entity->setPos(entityPos);
}
