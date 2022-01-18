#ifndef __SUBJECT_H__
#define __SUBJECT_H__

#include <vector>
#include <memory>
#include "observer.h"

class Subject {
    std::vector<std::unique_ptr<Observer>> observers;
  public:
    virtual ~Subject();
    void notifyObservers();
    void attach(Observer *obs);
    void detach(Observer *obs);
};

#endif
