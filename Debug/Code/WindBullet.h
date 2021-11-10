#pragma once
#include "Bullet.h"

class WindBullet : public Bullet
{
private:
	int invFlag;
public:
	WindBullet(Vector2f location, Vector2f targetLocation, float attack, double angle, float speed);
	int PlayAnimation();
};

