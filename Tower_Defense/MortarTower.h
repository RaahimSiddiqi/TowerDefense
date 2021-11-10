#pragma once
#include "tower.h"

class MortarTower : public Tower {
public:
	MortarTower();
	void Attack(Vector2f, int, float);
	std::shared_ptr<Tower> getClassObject();
	void Upgrade();
};
