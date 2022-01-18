#ifndef __PLAYER_CONTROLLED_H__
#define __PLAYER_CONTROLLED_H__

#include <memory>
#include "movement.h"
#include "../observer/modelStateObserver.h"

class Entity;

class PlayerControlled: public Movement {
	protected:
		virtual void doMove(Entity *entity, std::string action);
    public:
		PlayerControlled();
		~PlayerControlled() = default;
		virtual void move(Entity *entity) override;
		virtual void move(Entity *entity, std::string action);
};

#endif
