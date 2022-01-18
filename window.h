#ifndef __WINDOW___H__
#define __WINDOW___H__
#include <map>
#include "model.h"
#include "state.h"
#include "borderDirection.h"

class Entity;
class Border;
class Level;

class Window: public Model {
  protected:
    	struct Cell {
      		const int row, col;
      		State state;
      		Cell(int row, int col, State state);
      		Cell(int row, int col);
    	};

    	int rows = 22;
    	int cols = 80;
    	bool isBorderSolid;
    	std::vector<std::vector<Cell>> grid;
    	std::vector<std::unique_ptr<Entity>> entities;
    	std::unique_ptr<Border> border;
	std::vector<std::unique_ptr<Level>> levels;
	std::vector<Entity *> entitiesToDestroy;

	bool isWinner = false;
	bool isGameOver = false;
	bool isLevelOver = false;

	int score = 0;

	std::string playerAction;

    	void updateCell(int row, int col, State state);
	void collideEntityWithBorder(Entity *entity, BorderDirection direction);
	void doDestroyEntities();
  public:
    	Window(bool isBorderSolid=true);
    	~Window();

    	virtual void update(Entity *entity);
	virtual void update(Level *level);
	State getState(int row, int col);

	bool doesOverlap(Entity *entity1, Entity *entity2);
    	bool shouldRender(Entity *entity);
    	Entity *getEntity(int row, int col);
	int getNumberOfEntities();

	std::vector<int> getPlayerPosition();

	virtual void addLevel(std::unique_ptr<Level> level);
    	virtual void addEntity(std::unique_ptr<Entity> entity);
    	virtual void destroyEntity(Entity *entity);

    	virtual void moveEntities();
    	virtual void checkCollisions(Entity *entity);
	
	int getScore();
	void setScore(int n);

	std::string getAction() override;
	void triggerLevelEnd();
    	void triggerWin();
    	void triggerLoss();
    	virtual bool play();
	bool connectToAndRenderEntity(Entity *entity);
};

#endif

