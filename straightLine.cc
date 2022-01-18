#include "straightLine.h"
#include "../entity/entity.h"

StraightLine::StraightLine(int x, int y, int z): direction {std::vector<int> {x, y, z}} {}

StraightLine::~StraightLine() {}

void StraightLine::move(Entity *entity) {
    std::vector<int> entityPos = entity->getPos();
    entityPos[0] += direction[0];
    entityPos[1] += direction[1];
    entityPos[2] += direction[2];

    entity->setPos(entityPos);
}
