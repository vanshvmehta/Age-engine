#include "singleChar.h"
#include <iostream>

SingleChar::SingleChar(char c): shapeChar{c} {}

SingleChar::~SingleChar() {}

SingleChar::CharMap SingleChar::getShape() {
    std::vector<std::unique_ptr<CharImpl>> charMap;
    charMap.emplace_back(std::move(std::make_unique<CharImpl> (0, 0, shapeChar)));

    return charMap;
}
