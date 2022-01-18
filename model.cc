#include "model.h"
#include "../controller/curseControl.h"
#include "../views/curseView.h"

void Model::updateViews(int row, int col, State s) { for( auto& view: views ) view->update(row, col, s); }

void Model::updateStatus(int statusLine, std::string& str){
  for( auto& view: views ){
    if (statusLine == 1) view->setStatusLine1(str);
    else if (statusLine == 2) view->setStatusLine2(str);
    else if (statusLine == 3) view->setStatusLine3(str);
  }
}

void Model::displayViews() { for( auto& view: views ) view->displayView(); }

void Model::addView(std::unique_ptr<View> v){ views.emplace_back(std::move(v)); }

void Model::addController(std::unique_ptr<Controller> c) { control = std::move(c); }

std::string Model::getAction() { return control->getAction(); }
