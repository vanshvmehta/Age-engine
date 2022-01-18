#ifndef __EMPTY_SHAPE_H__
#define __EMPTY_SHAPE_H__

#include "shape.h"

class EmptyShape: public Shape {
  public:
    EmptyShape();
    ~EmptyShape() = default;
    CharMap getShape() override;
};

#endif
