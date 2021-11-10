#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

class Spell
{
public:
	Spell(Vector2f);
	Spell(Vector2f, int);
	Spell(Vector2f, float);
	Spell(int);
	void Attack(Vector2f pos);
	void Attack();
	int Update();
	int active = 0;
	int damage = 0;
	int turns = 0;
	Vector2f spritesheetsize;
	Vector2f spritesize;
	Sprite sprite;
	Clock clock;
	void Animate();
	IntRect rect = IntRect(0, 0, 115, 300);
	int duration;
};

