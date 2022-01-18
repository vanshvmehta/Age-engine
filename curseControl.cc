#include "curseControl.h"
#include <iostream>
#include <string>

CurseKeyboard::CurseKeyboard() {
  setlocale(LC_ALL, "");
  mapping['w'] = "keyW";
  mapping['d'] = "keyD";
  mapping['s'] = "keyS";
  mapping['a'] = "keyA";
  mapping[KEY_UP] = "up";
  mapping[KEY_RIGHT] = "right";
  mapping[KEY_DOWN] = "down";
  mapping[KEY_LEFT] = "left";
}

std::string CurseKeyboard::action(){
  int n;
  if ((n = getch()) == ERR) return "";
  if (mapping.find(n) != mapping.end()) { return mapping[n]; }
  return "";
}

void CurseKeyboard::addKey(char c, std::string str) { mapping[c] = str; }
