#pragma once
#include "tower.h"


class basicTower : public Tower {
public:
	basicTower();
	void Attack(Vector2f, int, float);
	std::shared_ptr<Tower> getClassObject();
	void Upgrade();
};


