#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__

#include "shape.h"

class Rectangle: public Shape {
	int rows, cols;
	char shapeChar;

    public:
	Rectangle(int rows, int cols, char c);
	~Rectangle() = default;
	CharMap getShape() override;	
};

#endif
