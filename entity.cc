#include "entity.h"
#include "../movement/straightLine.h"
#include <iostream>

Entity::Entity(int x, int y, int z, std::unique_ptr<Shape> shape): pos{std::vector<int> {x, y, z}},
    oldPos{std::vector<int> {x, y, z}}, shape{std::move(shape)} {}

std::vector<int> Entity::getPos() { return pos; }

std::vector<int> Entity::getOldPos() { return oldPos; }

void Entity::setPos(std::vector<int> newPos) {
    oldPos = pos;
    pos = newPos;
    notifyPropertyObservers();
}

std::vector<std::unique_ptr<CharImpl>> Entity::getShape() { return shape->getShape(); }

void Entity::move() { for (auto &it: movements) it->move(this); }

void Entity::addMovement(std::unique_ptr<Movement> movement) { movements.emplace_back(std::move(movement)); }

void Entity::removeMovement(Movement *movement) {
    for (auto it = movements.begin(); it != movements.end(); ++it) {
        if (it->get() == movement) {
            movements.erase(it);
            break;
        }
    }
}

bool Entity::isPlayerControlled() { return playerControlled; }

void Entity::collideWithTag(PassThrough) {}

void Entity::collideWithTag(CollideAndDestroy) {
	notifyStateObservers(DestroyEntityTag {}, this);
}

void Entity::collideWithTag(CollideAndBounce) {
	pos = oldPos;
	notifyPropertyObservers();
}

void Entity::collideWithTag(CollideAndTakeDamage, int damage) {
	if (hasHealth) {
		health -= damage;
		if (health <= 0) notifyStateObservers(DestroyEntityTag {}, this);
	}
}

void Entity::collideWithTag(CollideAndTriggerWin) {
	notifyStateObservers(TriggerWinTag {});
}

void Entity::collideWithTag(CollideAndTriggerLoss) {
	notifyStateObservers(TriggerLossTag {});
}

void Entity::collideWithTag(CollideAndStop) {
	pos = oldPos;
	movements.clear();
	notifyPropertyObservers();
}

void Entity::collideWithTag(CollideAndHeal, int amount) {
	if (hasHealth) health += amount;
}
