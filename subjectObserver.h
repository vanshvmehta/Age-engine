#ifndef __SUBJECT_OBSERVER_H__
#define __SUBJECT_OBSERVER_H__

#include <memory>
#include "observer.h"
#include "../model/window.h"
#include <iostream>

template<typename Subject> 
class SubjectObserver: public Observer {
  protected:
    Subject *subject;
    Window *object;

  public:
    SubjectObserver(Subject *subject, Window *window): subject {subject}, object {window} {}
    ~SubjectObserver() { subject->detach(this); }
    void notify() override { object->update(subject); }
};

#endif
