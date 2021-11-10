#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "tower.h"
#include "button.h"




using namespace sf;
using namespace std;

class DisplayMenu {
private:
	RectangleShape DMenu;
	int money = 2000;
	int maxHealth = 100;
	int health = 100;
	Text TitleText;
	Text HealthText;
	Text AttackText;
	Text NameText;
	Text SpeedText;
	Text RangeText;
	Text MoneyText;
	Text FPSText;
	Text ProjectileSpeedText;
	Text Title1;
	Text Title2;
	Text Wave;
	Text Lvl;
	Text value;
	Text UpgradeCost;
	Vector2f Origin;
	Sprite Wood1;
	Sprite Wood2;


	Clock UpdateClock;
	Time elapsedTime;
	
	Button Upgradebutton;
	Button Destroybutton;

public:
	DisplayMenu(Vector2f);
	~DisplayMenu();
	std::shared_ptr<Tower> tower;
	int selected = 0;
	//Tower* tower;
	
	Sprite selectedSprite;
	static DisplayMenu* getInstance();
	void setMoney(int);
	int getMoney();
	Sprite sprite;
	void Update(Vector2f);
	void Draw();
	static DisplayMenu* instance;
	
	int setHealth(int, int);
	float getHealth();

	void UpdateButtons();
	void UpdateFPS();
	void ExecuteEvents(int ID);
};

