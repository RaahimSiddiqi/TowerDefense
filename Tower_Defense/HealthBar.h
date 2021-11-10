#pragma once
#include "SFML/Graphics.hpp"

using namespace sf;

class HealthBar
{
private:
	int _health;
	int _maxHealth;
	Vector2f HealthSize;
public:


	HealthBar(int);
	HealthBar() { _health = 0;  _maxHealth = 0;  };
	void setSize(Vector2f);
	int getHealth();
	int HealthCheck();
	void updateHealth(int health);
	RectangleShape hbar;
};

