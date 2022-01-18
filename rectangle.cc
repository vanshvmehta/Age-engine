#include <memory>
#include "rectangle.h"
#include "charImpl.h"

Rectangle::Rectangle(int rows, int cols, char c): rows{rows}, cols{cols}, shapeChar{c} {}

Shape::CharMap Rectangle::getShape() {
	CharMap charMap;
	for (int col = 0; col < cols; ++col) {
		for (int row = 0; row < rows; ++row) {
		       charMap.emplace_back(std::make_unique<CharImpl> (row, col, shapeChar));
		}
 	}
	return charMap;
}	
