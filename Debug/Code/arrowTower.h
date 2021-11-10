#pragma once
#include "tower.h"

class arrowTower : public Tower {
public:
	arrowTower();
	void Attack(Vector2f, int, float);
	std::shared_ptr<Tower> getClassObject();
	void Upgrade();
};
