#include "curseView.h"
#include <ncurses.h>
#include "../model/window.h"
#include <iostream>
#include "../entity/entity.h"

Curses::Curses(int rows, int cols, Window &win): rows{rows}, cols{cols}, model{win} {
  setlocale(LC_ALL, "");
  initscr();
  noecho();
  cbreak();
  halfdelay(5);
  keypad(stdscr, TRUE);
  curs_set(0);
  
  // Exterior walls
  for (int i = 0; i < cols; ++i){
    mvwaddch(stdscr, 0, i, ACS_HLINE);
    mvwaddch(stdscr, rows - 4, i, ACS_HLINE);
  }

  for (int i = 0; i < rows - 3; ++i){
    mvwaddch(stdscr, i, 0, ACS_VLINE);
    mvwaddch(stdscr, i, cols - 1, ACS_VLINE);
  }

  // Corners
  mvwaddch(stdscr, 0, 0, ACS_ULCORNER);
  mvwaddch(stdscr, 0, cols - 1, ACS_URCORNER);
  mvwaddch(stdscr, rows - 4, 0, ACS_LLCORNER);
  mvwaddch(stdscr, rows - 4, cols - 1, ACS_LRCORNER);
}

Curses::~Curses(){ endwin(); }

void Curses::setStatusLine1(std::string &str) { update(1, str); }

void Curses::setStatusLine2(std::string &str) { update(2, str); }

void Curses::setStatusLine3(std::string &str) { update(3, str); }

void Curses::displayView(){
	for (int row = 1; row < rows - 4; ++row) {
		for (int col = 1; col < cols - 1; ++col) {
	     		std::string emptyString = " ";
    			mvprintw(row, col, emptyString.c_str());
		}
	}
	
	for (int row = 1; row < rows - 4; ++row) {
    		for (int col = 1; col < cols - 1; ++col) {
   	   		if (model.getState(row, col) == State::ENTITY_HEAD) {
	//			++count;
	//			std::string msg = "Drawing Entity" + std::to_string(count);
	//			setStatusLine1(msg);
        			Entity *entity = model.getEntity(row, col);
				if (entity == nullptr);
				else drawEntity(entity);

	//			msg = "Drew Entity" + std::to_string(count);
	//			setStatusLine2(msg);
      			}
   		}
  	}
  	refresh();
}

void Curses::update(int statusLine, std::string& msg){
  if (!((statusLine > 0) and (statusLine < 4))) return;

  move(rows - (4 - statusLine), 0);
  clrtoeol();

  mvprintw(rows - (4 - statusLine), 0, msg.c_str());
}

void Curses::update(int row, int col, State state) {
    if (state == State::EMPTY) update(row, col, EmptyTag());
    else if (state == State::ENTITY_HEAD) update(row, col, EntityHeadTag());
    else if (state == State::ENTITY_BODY) update(row, col, EntityBodyTag());
}

void Curses::update(int row, int col, EmptyTag) {}

void Curses::update(int row, int col, BorderTag) {}

void Curses::update(int row, int col, EntityHeadTag) {}

void Curses::update(int row, int col, EntityBodyTag) {}

void Curses::drawEntity(Entity *entity) {
  	CharMap charMap = entity->getShape();
  	std::vector<int> entityPos = entity->getPos();
  	for (auto &it: charMap) {
    		std::string shapeChar = std::string(1, it->shapeChar);
		// std::cout << it->shapeChar << std::endl;
    		mvprintw(entityPos[1] + it->y, entityPos[0] + it->x, shapeChar.c_str());
 	}
}

