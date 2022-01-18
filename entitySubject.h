#ifndef __ENTITY_SUBJECT_H__
#define __ENTITY_SUBJECT_H__

#include <vector>
#include <memory>
#include <string>
#include "subject.h"
#include "../model/modelState.h"

class Entity;
template <typename Subject> class ModelStateObserver;
template <typename Subject> class SubjectObserver;

class EntitySubject: public Subject {
    std::vector< std::unique_ptr<SubjectObserver<Entity>>> propertObservers;
    std::vector< std::unique_ptr<ModelStateObserver<Entity>> > modelStateObservers;

  public:
    EntitySubject();
    ~EntitySubject();

    void notifyPropertyObservers();
    void notifyStateObservers(TriggerWinTag);
    void notifyStateObservers(TriggerLossTag);
    void notifyStateObservers(CreateEntityTag, std::unique_ptr<Entity> entity);
    void notifyStateObservers(DestroyEntityTag, Entity *entity);
    void notifyStateObservers(IncrementScoreTag, int n);
    void notifyStateObservers(UpdateStatusTag, int statusLine, std::string &msg);

    std::string getAction();
    std::vector<int> getPlayerPosition();

    virtual void attachPropertyObserver(std::unique_ptr<SubjectObserver<Entity>> observer);
    virtual void detachPropertyObserver(SubjectObserver<Entity> *observer);

    virtual void attachModelStateObservers(std::unique_ptr<ModelStateObserver<Entity>> observer);
    virtual void detachModelStateObservers(ModelStateObserver<Entity> *observer);
};

#endif
