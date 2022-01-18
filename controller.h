#ifndef ___CONTROLLER___H__
#define ___CONTROLLER___H__

#include <string>

class Controller{
  virtual std::string action() = 0;
 public:
  std::string getAction();
  virtual ~Controller() = default;
  virtual void addKey(char c, std::string str) = 0;
};
#endif
