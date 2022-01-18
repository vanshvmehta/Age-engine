#ifndef ___SHAPE__H___
#define ___SHAPE__H___

#include <memory>
#include <vector>
#include "charImpl.h"


class Shape {
  public:
    typedef std::vector<std::unique_ptr<CharImpl>> CharMap;

    virtual ~Shape() = default;
    virtual CharMap getShape() = 0; 
};

#endif
