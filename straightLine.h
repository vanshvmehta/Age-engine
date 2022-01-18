#ifndef __STRAIGHT_LINE_H__
#define __STRAIGHT_LINE_H__

#include "movement.h"
#include <vector>

class Entity;

class StraightLine: public Movement {
    protected:
    	std::vector<int> direction;

  public:
    StraightLine(int x, int y, int z);
    ~StraightLine();
    void move(Entity *entity) override;
};

#endif
