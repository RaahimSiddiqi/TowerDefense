#pragma once
#include "Bullet.h"

class PoisonBullet : public Bullet
{
private:
	int invFlag;
public:
	PoisonBullet(Vector2f location, Vector2f targetLocation, float attack, double angle, float speed);
	int PlayAnimation();
};

