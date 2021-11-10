#include "HealthBar.h"
#include <iostream>

using namespace std;

HealthBar::HealthBar(int health) {
	_health = health;
	_maxHealth = health;
	HealthSize = Vector2f(50, 10);
	hbar.setSize(HealthSize);
	hbar.setFillColor(Color::Red);
}

int HealthBar::getHealth() {
	return _health;
}

void HealthBar::setSize(Vector2f size) {
	hbar.setSize(size);
	HealthSize = size;
}


void HealthBar::updateHealth(int health) {

	_health = health;
	hbar.setSize(Vector2f(HealthSize.x * ((float)_health / _maxHealth), HealthSize.y));
}


int HealthBar::HealthCheck() {
	if (_health <= 0) {
		return 1;
	}
	return 0;
}