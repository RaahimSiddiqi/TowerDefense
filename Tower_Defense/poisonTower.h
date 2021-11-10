#pragma once
#include "tower.h"

using namespace std;
using namespace sf;

class poisonTower : public Tower
{
private:
	float duration;
public:
	poisonTower();
	void Attack(Vector2f, int, float);
	void Upgrade();
};

