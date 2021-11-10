#pragma once
#include "Bullet.h"

class MudBullet : public Bullet
{
public:
	MudBullet(Vector2f location, Vector2f targetLocation, float attack);
	MudBullet(Vector2f location, Vector2f targetLocation, float attack, float speed);
	int PlayAnimation();
};

