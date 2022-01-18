#ifndef __CURSE_KEYBOARD___H__
#define __CURSE_KEYBOARD___H__

#include "controller.h"
#include <iostream>
#include <string>
#include <map>
#include <ncurses.h>


class Mapping;

class CurseKeyboard: public Controller{
  std::map<int, std::string> mapping; 

  std::string action() override;
 public:
  CurseKeyboard();
  void addKey(char c, std::string str) override;
};
#endif
