#ifndef __BITMAP_H__
#define __BITMAP_H__

#include <vector>
#include <memory>
#include "shape.h"

class incorrectBitMapError{};

class Bitmap: public Shape {
	std::vector<int> xs, ys;
	std::vector<char> cs;

    public:
	Bitmap(std::vector<int> xs, std::vector<int> ys, std::vector<char> cs);
	~Bitmap() = default;
	CharMap getShape();
};	

#endif
