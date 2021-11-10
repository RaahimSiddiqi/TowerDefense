#pragma once
#include "tower.h"

class magicTower : public Tower {
public:
	magicTower();
	void Attack(Vector2f, int, float);
	std::shared_ptr<Tower> getClassObject();
	void Upgrade();
};
