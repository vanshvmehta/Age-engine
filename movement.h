#ifndef __MOVEMENT_H__
#define __MOVEMENT_H__

#include <vector>

class Entity;

class Movement {
  public:
    virtual ~Movement() = default;
    virtual void move(Entity *entity) = 0;
};

#endif