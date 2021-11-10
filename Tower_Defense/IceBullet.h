#pragma once
#include "Bullet.h"


class IceBullet : public Bullet
{
public: 
	IceBullet(Vector2f location, Vector2f targetLocation, float attack);
	IceBullet(Vector2f location, Vector2f targetLocation, float attack, float speed, float duration, double angle);
	int PlayAnimation() override;
};

