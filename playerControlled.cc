#include <string>
#include <vector>
#include "playerControlled.h"
#include "../entity/entity.h"

PlayerControlled::PlayerControlled() {}

void PlayerControlled::move(Entity *entity) {
	std::string action = entity->getAction();
	doMove(entity, action);
}

void PlayerControlled::move(Entity *entity, std::string action) { doMove(entity, action); }

void PlayerControlled::doMove(Entity *entity, std::string action) {
	std::vector<int> entityPos = entity->getPos();
        if (action == "up") --entityPos[1];
        else if (action == "down") ++entityPos[1];
        else if (action == "left") --entityPos[0];
        else if (action == "right") ++entityPos[0];
        else return;

        entity->setPos(entityPos);
}
