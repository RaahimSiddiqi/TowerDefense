#pragma once
#include "Bullet.h"

class MagicBullet : public Bullet
{
public:
	MagicBullet(Vector2f location, Vector2f targetLocation, float attack, double angle, float speed);
	int PlayAnimation();
};



