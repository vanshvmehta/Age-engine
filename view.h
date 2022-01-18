#ifndef ___VIEW___H__
#define ___VIEW___H__

#include <string>
#include "../model/state.h"
#include <vector>
#include <memory>

class CharImpl;

class View{
 public:
  virtual ~View() = default;
  virtual void update(int row, int col, State state) = 0;
  // virtual void update(int row, int col, std::vector<std::unique_ptr<CharImpl>> charMap) = 0;
  virtual void setStatusLine1(std::string &str) = 0;
  virtual void setStatusLine2(std::string &str) = 0;
  virtual void setStatusLine3(std::string &str) = 0;
  virtual void displayView() = 0;
};

#endif
