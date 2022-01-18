#ifndef __BORDER_H__
#define __BORDER_H__

#include "entity.h"
#include <map>

enum BorderDirection;
struct ColissionsTag;

class Border: public Entity {
    	std::map<int, std::vector<Entity *>> entityMap;
    	int row, col;
    	bool isSolid;

   public:
    	Border(int row, int col, bool isSolid=true);
    	~Border();

    	void move() override;
    	void collideWith(Entity *entity) override;
	void collideWith(Border *border, BorderDirection direction) override;
};

#endif
