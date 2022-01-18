#ifndef __GRAVITY_H__
#define __GRAVITY_H__

#include <vector>
#include "movement.h"
#include "../model/borderDirection.h"

class Entity;

class Gravity: public Movement {
	std::vector<int> direction;
    public:
	Gravity(BorderDirection border);
	~Gravity() = default;
	void move(Entity *entity) override;
};

#endif
