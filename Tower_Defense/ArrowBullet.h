#pragma once
#include "Bullet.h"

class ArrowBullet : public Bullet
{
public:
	ArrowBullet(Vector2f location, Vector2f targetLocation, float attack, double angle);
	ArrowBullet(Vector2f location, Vector2f targetLocation, float attack, double angle, float speed);
	int PlayAnimation();
};

