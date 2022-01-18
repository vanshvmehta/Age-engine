#include "level.h"
#include "../observer/modelStateObserver.h"
#include "../model/modelState.h"

Level::Level() {}

Level::~Level() {}

void Level::attach(std::unique_ptr<ModelStateObserver<Level>> obs) { observer = std::move(obs); }

void Level::detach(ModelStateObserver<Level> *obs) { observer.release(); }

