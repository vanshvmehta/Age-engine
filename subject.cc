#include "subject.h"
#include "observer.h"

Subject::~Subject() {}

void Subject::notifyObservers() { for (auto &it: observers) it->notify(); }

void Subject::attach(Observer *obs) { 
    observers.emplace_back(std::move(std::unique_ptr<Observer> (obs)));
}

void Subject::detach(Observer *obs) { 
    for (auto it = observers.begin(); it != observers.end(); ++it) {
        if (it->get() == obs) { 
            observers.erase(it);
            break;
        }
    }
}
