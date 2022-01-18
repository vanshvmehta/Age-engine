#include "entitySubject.h"
#include "../model/modelState.h"
#include "../entity/entity.h"
#include "modelStateObserver.h"
#include "subjectObserver.h"

EntitySubject::EntitySubject() {}

EntitySubject::~EntitySubject() {}

void EntitySubject::notifyPropertyObservers() { for (auto &it: propertObservers) it->notify(); }

void EntitySubject::notifyStateObservers(TriggerWinTag) {
    for (auto &it: modelStateObservers) it->notify(TriggerWinTag{});
}

void EntitySubject::notifyStateObservers(TriggerLossTag) {
    for (auto &it: modelStateObservers) it->notify(TriggerLossTag{});
}

void EntitySubject::notifyStateObservers(CreateEntityTag, std::unique_ptr<Entity> entity) {
    for (auto &it: modelStateObservers) it->notify(CreateEntityTag {}, std::move(entity));
}

void EntitySubject::notifyStateObservers(DestroyEntityTag, Entity *entity) {
    for (auto &it: modelStateObservers) it->notify(DestroyEntityTag {}, entity);
}

void EntitySubject::notifyStateObservers(IncrementScoreTag, int n) {
	for (auto &it: modelStateObservers) it->notify(IncrementScoreTag {}, n);
}

void EntitySubject::notifyStateObservers(UpdateStatusTag, int statusLine, std::string &msg) {
	for (auto &it: modelStateObservers) it->notify(UpdateStatusTag {}, statusLine, msg);
}

std::string EntitySubject::getAction() { return modelStateObservers[0]->getAction(); }

std::vector<int> EntitySubject::getPlayerPosition() { return modelStateObservers[0]->getPlayerPosition(); }

void EntitySubject::attachPropertyObserver(std::unique_ptr<SubjectObserver<Entity>> observer) {
    propertObservers.emplace_back(std::move(observer));
}

void EntitySubject::detachPropertyObserver(SubjectObserver<Entity> *observer) {
    for (auto it = propertObservers.begin(); it != propertObservers.end(); ++it) {
        if ((*it).get() == observer) {
            propertObservers.erase(it);
            break;
        }
    }
}

void EntitySubject::attachModelStateObservers(std::unique_ptr<ModelStateObserver<Entity>> observer) {
    modelStateObservers.emplace_back(std::move(observer));
}

void EntitySubject::detachModelStateObservers(ModelStateObserver<Entity> *observer) {
    for (auto it = modelStateObservers.begin(); it != modelStateObservers.end(); ++it) {
        if ((*it).get() == observer) {
            modelStateObservers.erase(it);
            break;
        }
    }
}
