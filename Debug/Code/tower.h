#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <math.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include "Tile.h"
#include "Enemy.h"

using namespace sf;
using namespace std;


class Tower {
	friend void displayDetails(shared_ptr<Tower>& t);

protected:
	int following = 1;
	int selected = 0;
	void Draw();
	float attack = 0;
	int cooldownFlag = 0;
	float cooldown = 0;
	float projectileSpeed = 0;
	int level = 1;
	int cost;
	int value;
	Time time;
	Clock clock;
	float offset1;
	float offset2;
	IntRect rect;
	Vector2f size = Vector2f(20, 20);
	int checkTiles();
	int ContactTileColoring(Color color);


public:
	Texture *texture;
	string displayName;
	Sprite sprite;
	CircleShape range;
	shared_ptr<Enemy> selectedEnemy;

	Sprite A1;
	Sprite A2;
	Texture ArrowTexture;

	Tower();
	~Tower();
	string name = "Tower";
	int builtFlag = 0;
	bool isSelected = false;
	void followMouse();
	void Update();
	void setAttack(float attack);
	void setFollowing(int value);
	float getAttack();
	float getSpeed();
	float getRefund();
	int getValue();
	int getCost();
	virtual void Upgrade();
	int checkCost();
	int checkUpgradeCost();
	int getLevel();
	float getProjectileSpeed();
	float getRange();
	void DestroyTower();
	void FoilageCollisionCheck();

	virtual void Attack(Vector2f, int, float) = 0;
	Vector2f TowerAI(Vector2f, Vector2f, float, float, int);

	Tower& getInstance();
	void removeContactColoring();
	void removeContactTiles();
	void TileContact();
	double fireCalcAngle(Vector2f, Vector2f, Vector2f);

	vector<Tile*> contactTiles;
};

