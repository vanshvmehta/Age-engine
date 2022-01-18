#ifndef __MODEL_STATE_OBSERVER_H__
#define __MODEL_STATE_OBSERVER_H__

#include "observer.h"
#include "../model/modelState.h"
#include <iostream>
#include "../model/window.h"

class Entity;

template <typename Subject>
class ModelStateObserver: public Observer {
	Subject *subject;
	Window *window;
    public:
    	ModelStateObserver(Subject *subject, Window *window): subject{subject}, window{window} {}
    	~ModelStateObserver() { subject->detach(this); };

	void notify() override { window->update(subject); }
    	void notify(CreateEntityTag, std::unique_ptr<Entity> entity) { window->addEntity(std::move(entity)); }
    	void notify(DestroyEntityTag, Entity *entity) { window->destroyEntity(entity); }
   	void notify(TriggerWinTag) { window->triggerWin(); }
    	void notify(TriggerLossTag) { window->triggerLoss(); }
	void notify(TriggerLevelEndTag) { window->triggerLevelEnd(); }
	void notify(IncrementScoreTag, int n) { window->setScore(window->getScore() + n); }
	void notify(UpdateStatusTag, int statusLine, std::string &msg) { window->updateStatus(statusLine, msg); }
	std::string getAction() { return window->getAction(); }
	int getScore() { return window->getScore(); }
	std::vector<int> getPlayerPosition() { return window->getPlayerPosition(); }

	Entity * getEntity(int row, int col) { return window->getEntity(row, col); }
	int getNumberOfEntities() {return window->getNumberOfEntities(); }
};

#endif
