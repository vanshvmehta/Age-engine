#include "bitmap.h"
#include "charImpl.h"

Bitmap::Bitmap(std::vector<int> xs, std::vector<int> ys, std::vector<char> cs): xs{xs}, ys{ys}, cs{cs} {
	int length = xs.size();
	if ((ys.size() != length) or (cs.size() != length)) throw incorrectBitMapError{};
}

Shape::CharMap Bitmap::getShape() {
	CharMap charMap;
	for (int i = 0; i < xs.size(); ++i) {
		charMap.emplace_back(std::move(std::make_unique<CharImpl> (xs[i], ys[i], cs[i])));
	}
	return charMap;
}
