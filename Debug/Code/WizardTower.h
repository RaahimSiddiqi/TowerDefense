#pragma once
#include "tower.h"

class wizardTower : public Tower {
public:
	wizardTower();
	void Attack(Vector2f, int, float);
	void Upgrade();
};
