#include "border.h"
#include "../shape/emptyShape.h"

Border::Border(int row, int col, bool isSolid): 
	Entity{col, row, 0, std::move(std::make_unique<EmptyShape> ())}, row{row}, col{col}, isSolid{isSolid}
{
    if (isSolid) return;
    for (int i = 1; i < 6; ++i) entityMap[i] = std::vector<Entity *> ();
}

Border::~Border() {}

void Border::move() {
    if (isSolid) return;

    for (auto &it: entityMap[5]) { notifyStateObservers(DestroyEntityTag {}, it); }
    for (int i = 4; i > 0; --i) { entityMap[i + 1] = entityMap[i]; }
    entityMap[1].clear();
}

void Border::collideWith(Entity *entity) {
    if (isSolid) return;

    if (entity->isPlayerControlled()) {
        entity->collideWith(this);
        entity->setPos(entity->getOldPos());
    }
    
    else {
        for (int i = 1; i < 6; ++i) {
            for (auto it = entityMap[i].begin(); it != entityMap[i].end(); ++it) {
                if (*it == entity) entityMap[i].erase(it);
                return;
            }
        }
    }

    entityMap[1].emplace_back(entity);
}

void Border::collideWith(Border *border, BorderDirection direction) {}
