#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <memory>
#include <vector>

template <typename Subject> class ModelStateObserver;

class Level {
    protected:	
	std::unique_ptr<ModelStateObserver<Level>> observer;
    public:
	Level();
	virtual ~Level();
	void attach(std::unique_ptr<ModelStateObserver<Level>> observer);
	void detach(ModelStateObserver<Level> *obs);
	std::vector<int> getPos() { return std::vector<int> {1,1,1}; }
	virtual void tick() = 0;
};

#endif
