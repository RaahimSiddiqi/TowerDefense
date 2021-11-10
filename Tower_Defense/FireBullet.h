#pragma once
#include "Bullet.h"

class FireBullet : public Bullet
{
public:
	FireBullet(Vector2f location, Vector2f targetLocation, float attack, double angle, float speed);
	int PlayAnimation();
};

