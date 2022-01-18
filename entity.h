#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "../shape/shape.h"
#include "../movement/movement.h"
#include "../observer/entitySubject.h"
#include "../model/borderDirection.h"
#include "../colission/colissionsTag.h"
#include <vector>
#include <memory>


class Border;

class Entity: public EntitySubject {
  protected:
    std::unique_ptr<Shape> shape;
    std::vector<int> oldPos, pos;
    std::vector<std::unique_ptr<Movement>> movements;
    bool playerControlled = false;
	bool hasHealth = false;
	int health = 0;

  public:
    Entity(int x, int y, int z, std::unique_ptr<Shape> shape);
    virtual ~Entity() = default;

    std::vector<int> getPos();
    std::vector<int> getOldPos();
    void setPos(std::vector<int> newPos);
    std::vector<std::unique_ptr<CharImpl>> getShape();

    virtual void move();
    void addMovement(std::unique_ptr<Movement> movement);
    void removeMovement(Movement *movement);

    virtual void collideWith(Entity *entity) = 0;
    virtual void collideWith(Border *entity, BorderDirection direction) = 0;
    
    virtual void collideWithTag(PassThrough);
    virtual void collideWithTag(CollideAndDestroy);
    virtual void collideWithTag(CollideAndBounce);
	virtual void collideWithTag(CollideAndTakeDamage, int damage);
	virtual void collideWithTag(CollideAndTriggerWin);
	virtual void collideWithTag(CollideAndTriggerLoss);
	virtual void collideWithTag(CollideAndStop);
	virtual void collideWithTag(CollideAndHeal, int amount);

    bool isPlayerControlled();
};

#endif
