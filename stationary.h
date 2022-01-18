#ifndef __STATIONARY_H__
#define __STATIONARY_H__

#include "movement.h"

class Entity;

class Stationary: public Movement {
    public:
	    Stationary() = default;
	    ~Stationary() = default;
	    void move(Entity *entity) override;
};

#endif
