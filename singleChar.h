#ifndef __SINGLE_CHAR_H__
#define __SINGLE_CHAR_H__

#include <memory>
#include "shape.h"

class SingleChar: public Shape {
  char shapeChar;

  public:
    SingleChar(char c);
    ~SingleChar();
    std::vector<std::unique_ptr<CharImpl>> getShape() override;
};

#endif
