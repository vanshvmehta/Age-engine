#include "periodicMovement.h"

PeriodicMovement::PeriodicMovement(int frequency): frequency{frequency} {tickCount = 0;}

void PeriodicMovement::move(Entity *entity) {
	++tickCount;
	if (tickCount >= frequency) {
		doMove(entity);
		tickCount = 0;
	}
}
