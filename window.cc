#include "window.h"
#include <string.h>
#include "../entity/entity.h"
#include "../entity/border.h"
#include "../views/curseView.h"
#include "../controller/curseControl.h"
#include "../observer/subjectObserver.h"
#include "../observer/modelStateObserver.h"
#include "../movement/playerControlled.h"
#include "../level/level.h"
#include <iostream>

Window::Cell::Cell(int row, int col, State state): 
    row {row}, col {col}, state{state} {}

Window::Cell::Cell(int row, int col): row{row}, col{col}, state{State::EMPTY} {}

Window::Window(bool isBorderSolid): isBorderSolid{isBorderSolid} {
    addView(std::move(std::make_unique<Curses>(25, 80, *this)));
    addController(std::move(std::make_unique<CurseKeyboard>()));

    for (int row = 0; row < rows; ++row) {
        std::vector<Window::Cell> gridRow;
        for (int col = 0; col < cols; ++col) {
            if ((row == 0) or (row == rows-1) or (col == 0) or (col == cols-1)) gridRow.emplace_back(Cell(row, col, State::BORDER));

            else gridRow.emplace_back(Cell(row, col));
        }
        grid.emplace_back(gridRow);
    }

    border = std::make_unique<Border> (rows, cols);
    border->attachModelStateObservers(std::make_unique<ModelStateObserver<Entity>> (border.get(), this));
}

Window::~Window() {}

void Window::updateCell(int row, int col, State state){
    	grid[row][col].state = state;
}

void Window::collideEntityWithBorder(Entity *entity, BorderDirection direction) {
	if (isBorderSolid) entity->collideWith(border.get(), direction);
        else border->collideWith(entity);
}

State Window::getState(int row, int col) {
	try {
		State state = grid.at(row).at(col).state;
		return state;	
	} catch (std::out_of_range ofr){ return EMPTY; }
}

void Window::addLevel(std::unique_ptr<Level> level) {
	level->attach(std::move(std::make_unique<ModelStateObserver<Level>> (level.get(), this)));
	levels.emplace_back(std::move(level));
}

void Window::addEntity(std::unique_ptr<Entity> entity) {
	if (connectToAndRenderEntity(entity.get())) entities.emplace_back(std::move(entity));
}

void Window::destroyEntity(Entity *entity) {
	entitiesToDestroy.emplace_back(entity);
}

void Window::doDestroyEntities() {
	for (auto &it: entitiesToDestroy) {
		for (auto entityIt = entities.begin(); entityIt != entities.end(); ++entityIt) {
			if ((*entityIt).get() == it) {
				entities.erase(entityIt);
				break;
			}
		}
	}
	entitiesToDestroy.clear();
}

bool Window::doesOverlap(Entity *entity1, Entity *entity2){
	std::vector<int> entity1Pos = entity1->getPos();
	std::vector<int> entity2Pos = entity2->getPos();

	Shape::CharMap entity1Shape = entity1->getShape();
	Shape::CharMap entity2Shape = entity2->getShape();

	for (auto &shape1It: entity1Shape) {
		for (auto &shape2It: entity2Shape) {
			if (((entity1Pos[0] + shape1It->x) == (entity2Pos[0] + shape2It->x)) and
			   ((entity1Pos[1] + shape1It->y) == (entity2Pos[1] + shape2It->y))) return true;
		}
	}
	return false;
}

bool Window::shouldRender(Entity *entity) {
	std::vector<int> entityPos = entity->getPos();
	Shape::CharMap entityShape = entity->getShape();
	bool value = true;
	for (auto &it: entities) {
		if (it.get() == entity) continue;
		else if (doesOverlap(entity, it.get())) {
			if (entityPos[2] > it->getPos()[2]) continue;
			else value = false;
		}
	}
	return value;
}

int Window::getNumberOfEntities() { return entities.size(); }

Entity *Window::getEntity(int row, int col) {
	std::vector<Entity *> highestEntity;
    bool found = false;

    for (auto it = entities.begin(); it != entities.end(); ++it) {
		std::vector<int> entityPos = (*it)->getPos();
		Shape::CharMap entityShape = (*it)->getShape();
		for (auto &entityShapeIt: entityShape) {
			if ((entityShapeIt->x + entityPos[0] == col) and (entityShapeIt->y + entityPos[1] == row)) {
				if (found) {
					if (highestEntity[0]->getPos()[2] >= entityPos[2]) continue;
					else highestEntity.insert(highestEntity.begin(), it->get());
				} else {
					highestEntity.emplace_back(it->get());
					found = true;
				}
			}
		}
	}	
	if (found) { return highestEntity[0]; }
	else { return nullptr; }
}

std::vector<int> Window::getPlayerPosition() {
	for (auto &it: entities) {
		if (it->isPlayerControlled()) return it->getPos();
	}

	return std::vector<int> {0, 0, 0};
}

void Window::update(Entity *entity) {
  	std::vector<int> oldPos = entity->getOldPos();
   	std::vector<int> newPos = entity->getPos();

	// if ((oldPos[0] == newPos[0]) and (oldPos[2] == newPos[2])) return;
   	std::vector<std::unique_ptr<CharImpl>> entityShape = entity->getShape();
	
	for (auto &it: entityShape) updateCell(oldPos[1] + it->y, oldPos[0] + it->x, State::EMPTY);
	
	for (auto &it: entityShape) {
		int row = newPos[1] + it->y;
		int col = newPos[0] + it->x;
		if (row <= 0) entity->collideWith(border.get(), BorderDirection::NORTH);
		else if (row >= rows - 4) entity->collideWith(border.get(), BorderDirection::SOUTH);
		else if (col >= cols - 1) entity->collideWith(border.get(), BorderDirection::EAST);
		else if (col <= 0) entity->collideWith(border.get(), BorderDirection::WEST);
		if ((row <= 0) or (row >= rows - 4) or (col > cols - 1) or (col <= 0)) return;
	}

   	updateCell(newPos[1], newPos[0], State::ENTITY_HEAD);

   	for (auto it = next(entityShape.begin(), 1); it != entityShape.end(); ++it) {
		updateCell(newPos[1] + (*it)->y, newPos[0] + (*it)->x, State::ENTITY_BODY);
	}

	checkCollisions(entity);
}

void Window::update(Level *level) {}

std::string Window::getAction() { return playerAction; }

void Window::moveEntities() { 
	std::vector<Entity *> playerControlled;
	for (auto &it: entities) {
		if (it->isPlayerControlled()) playerControlled.emplace_back(it.get());
		else it->move();
	}
	playerAction = Model::getAction();
	for (auto &it: playerControlled) it->move();
}

void Window::checkCollisions(Entity *entity) {
	std::vector<int> entityPos = entity->getPos();
	for (auto &it: entities) {
		if (it.get() == entity) continue;

		std::vector<int> objectPos = it->getPos();
		if (objectPos[2] != entityPos[2]) continue;
		else if (doesOverlap(entity, it.get())) entity->collideWith(it.get());
	}
}

void Window::setScore(int n) { score = n; }

int Window::getScore() { return score; }

void Window::triggerLevelEnd() { isLevelOver = true; }

void Window::triggerWin() {
	isWinner = true;
	isGameOver = true;
}

void Window::triggerLoss() {
	isWinner = false;
	isGameOver = true;
}

bool Window::play() { 
	const double NUM_SECONDS = 0.5;
    	double time_counter = 0;

    	clock_t this_time = clock();
    	clock_t last_time = this_time;
	int count = 0;
	int noOfLevels = levels.size();	
	auto currentLevelIt = levels.begin();
	while(true) {
		this_time = clock();
		time_counter += (double)(this_time - last_time);
		last_time = this_time;

		if(time_counter > (double)(NUM_SECONDS * CLOCKS_PER_SEC)) {
			if (isGameOver) break;
			if (isLevelOver) {
				++currentLevelIt;
				if (currentLevelIt == levels.end()) break;
				isLevelOver = false;
			}
			++count;
			time_counter -= (double)(NUM_SECONDS * CLOCKS_PER_SEC);
	//		std::string msg = "Displaying"+std::to_string(count);
	//		updateStatus(1, msg);
			displayViews();
//			msg = "Displayed"+std::to_string(count);
	//		updateStatus(1, msg);

	//		std::string msg2 = "Moving"+std::to_string(count);
	//		updateStatus(2, msg2);	

			moveEntities();
	//		msg2 = "Moved"+std::to_string(count);
	//		updateStatus(2, msg2);

	//		std::string msg3 = "Completed"+std::to_string(count);
	//		updateStatus(3, msg3);
			doDestroyEntities();
			if (noOfLevels > 0) (*currentLevelIt)->tick();
		}
	//std::string msg4 = "Waiting..."+std::to_string(count);
	//updateStatus(3, msg4);
	}
	return isWinner;
}

bool Window::connectToAndRenderEntity(Entity *entity) {
	std::vector<int> entityPos = entity->getPos();
        std::vector<std::unique_ptr<CharImpl>> entityShape = entity->getShape();

	for (auto &it: entityShape) {
                int row = entityPos[1] + it->y;
                int col = entityPos[0] + it->x;
                if ((row <= 0) or (row >= rows - 4) or (col > cols - 1) or (col <= 0)) return false;
        }

        entity->attachModelStateObservers(std::move(std::make_unique<ModelStateObserver<Entity>> (entity, this)));
        entity->attachPropertyObserver(std::move(std::make_unique<SubjectObserver<Entity>> (entity, this)));	

	updateCell(entityPos[1], entityPos[0], State::ENTITY_HEAD);

        for (auto it = next(entityShape.begin(), 1); it != entityShape.end(); ++it) {
                updateCell(entityPos[1] + (*it)->y, entityPos[0] + (*it)->x, State::ENTITY_BODY);
        }

	return true;
}

