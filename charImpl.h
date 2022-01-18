#ifndef __CHAR_IMPL_H__
#define __CHAR_IMPL_H__

struct CharImpl {
    int x, y;
    char shapeChar;
    
    CharImpl(int x, int y, char shapeChar): x{x}, y{y}, shapeChar{shapeChar} {}
};

#endif
