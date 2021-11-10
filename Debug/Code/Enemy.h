#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <math.h>
#include <iostream>
#include <vector>
#include "HealthBar.h"
#include "ToolTip.h"

using namespace sf;
using namespace std;


struct Effect {
	int ID;
	Clock timer;
	string name;
	int turn;
	int attack;
	int duration;
};

class Enemy {
protected:
	int money;
	int health;
	int maxHealth;
	int attack;
	int armor;
	string name;
	float speed;  // 3 speed settings, 1 - 2 - 4 (8 can be used too, but that and above is extreme)
	              // New update allows any speed value, not just multiples of 2
	int spriteSheetWidth;
	int offset = 0;
	int TextureRectWidth;
	int TextureRectHeight;
	Clock animationClock;

	// 0 for off, 1 for on
	int ydirection = 0; // Up
	int xdirection = 0; // Forward
	int zdirection = 0; // Down
	int minusxdirection = 0; // Backwards

public:

	Vector2f TileLoc;
	RectangleShape shape;
	Sprite sprite;
	IntRect texturePos;
	ToolTip tooltip;
	HealthBar healthBar;
	string info;
	

	vector<Effect> effects;
	void poisionEffect(float, int);
	void frostEffect();
	void frostEffect(int);
	void frozenEffect(int duration);
	void KnockBackEffect();
	void Effects();

	float TilesCovered = 0;

	void determineDirection();
	int getDirection();
	void Move(float speed);

	Enemy();
	void NextFrame();
	int takeDamage(int attack);
	int takeDamage(int attack, Color color);
	int takeDamage(int attack, Color color, string type);
	void setColor();

	float getSpeed();
	int getAttack() { return attack; }
	int getMoney() { return money; }
	int getHealth() { return health; }
	int getMaxHealth() { return maxHealth;  }
	int getArmor() { return armor; }
	void setHealth(int n) { health = n; }
	string getName() { return name; }

	void ApplyEffect(int i, float atk, int duration);
	Vector2f Offset;
	int frozen = 0;


	void UpdateToolTip();
	void Update();
	void Update(Vector2f MousePos);
};