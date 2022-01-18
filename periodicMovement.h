#ifndef __PERIODIC_MOVEMENT_H__
#define __PERIODIC_MOVEMENT_H__

#include "movement.h"

class Entity;

class PeriodicMovement: public Movement {
    protected:	
	int tickCount, frequency;
    public:
	PeriodicMovement(int frequency);
	~PeriodicMovement() = default;
	void move(Entity *entity) override;
    private:
	virtual void doMove(Entity *entity) = 0;
};

#endif
