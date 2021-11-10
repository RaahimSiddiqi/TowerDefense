#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

using namespace sf;
using namespace std;

class Bullet {
protected:
	float _attack = 0;
	int turn = 2;
	int texBurstOn = 0;
	string type;
	Clock timer;
	int effect = 0;
	int duration = 0;
	float speed;

public:
	CircleShape shot;
	RectangleShape beam;
	Sprite sprite;
	Vector2f origin;
	Vector2f target;
	Vector2f size;
	IntRect rect;

	int getEffect() { return effect; }
	int getTextureBurst() { return texBurstOn; }
	Bullet();
	void MoveToTarget();
	void Update();
	void Draw();
	string getType() { return type; };
	float getAttack();
	int getDuration() { return duration; };
	~Bullet();
	virtual int PlayAnimation() = 0;
	Texture tex;
	Texture burst;

};