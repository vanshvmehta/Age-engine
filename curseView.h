#ifndef __CURSES_VIEW___H__
#define __CURSES_VIEW___H__

#include "view.h"
#include <ncurses.h>
#include <vector>
#include <iostream>
#include <map>
#include <string>
#include "../model/state.h"
#include "../model/stateTag.h"


class Window;
class Entity;

class Curses: public View{
    int rows;
    int cols;
    Window& model;
    WINDOW *win;	

  public:
    Curses(int rows, int cols, Window &win);
    ~Curses();

    typedef std::vector<std::unique_ptr<CharImpl>> CharMap;

    void update(int row, int col, State state) override;
    void update(int row, int col, EmptyTag);
    void update(int row, int col, BorderTag);
    void update(int row, int col, EntityHeadTag);
    void update(int row, int col, EntityBodyTag);
    
    void displayView() override;

    void setStatusLine1(std::string &str) override;
    void setStatusLine2(std::string &str) override;
    void setStatusLine3(std::string &str) override;
  
  private:
    void update(int statusLine, std::string &str);
    void drawEntity(Entity *entity);
};

#endif
