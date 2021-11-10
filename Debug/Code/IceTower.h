#pragma once
#include "tower.h"

class IceTower : public Tower {
	int duration;
public:
	IceTower();
	void Attack(Vector2f, int, float);
	void Upgrade();

};

