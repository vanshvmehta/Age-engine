#ifndef ___MODEL____H_
#define ___MODEL____H_

#include <memory>
#include <vector>
#include <string>
#include "../controller/controller.h"
#include "../views/view.h"

class Model{
  std::vector<std::unique_ptr<View>> views;
  std::unique_ptr<Controller> control;
 protected:
  void addView(std::unique_ptr<View> v);
 public:
  virtual ~Model() = default;
  void updateViews(int, int, State);
  void updateStatus(int statusLine, std::string& s);
  void displayViews();
  void addController(std::unique_ptr<Controller> c);
  virtual std::string getAction();
};

#endif
