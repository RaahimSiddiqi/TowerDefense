#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <math.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include "CountDown.h"

using namespace sf;

class ConstructionMenu {
private:
	RenderWindow& Window;
	RectangleShape Cmenu;
	std::vector<Sprite> sprites;
	std::vector<Texture> textures;
	Sprite mainSprite;
	std::vector<int> cooldowns;

	CountDown spell1 = CountDown(Vector2f(760, 655), "90");
	CountDown spell2 = CountDown(Vector2f(850, 655), "90");
	CountDown spell3 = CountDown(Vector2f(935, 655), "120");

	Texture basicTowerTexture;
	Texture magicTowerTexture;
	Texture arrowTowerTexture;
	Texture poisonTowerTexture;
	Texture wizardTowerTexture;
	Texture iceTowerTexture;
	Texture mortarTowerTexture;

	Sprite Cost1;
	Sprite Cost2;
	Sprite Cost3;
	Sprite Cost4;
	Sprite Cost5;
	Sprite Cost6;
	Sprite Cost7;
	Sprite Cost8;
	Sprite Cost9;
	Sprite Cost10;
	Sprite Cost11;
	Vector2f Origin;

	
public:

	Sprite basicTower;
	Sprite magicTower;
	Sprite arrowTower;
	Sprite poisonTower;
	Sprite wizardTower;
	Sprite iceTower;
	Sprite mortarTower;
	Sprite IceSpell;
	Sprite LightningSpell;
	Sprite HealthRecoverSpell;

	ConstructionMenu(RenderWindow &window, Vector2f Origin);
	void updatePosition();
	void drawConstructionMenu();
	void Update();
	int SpellCast(int ID) {
		if (ID == 1) {
			if (spell1.Ready()) {
				spell1.ResetCount();
				spell1.startCount();
				return 1;
			}
		}
		if (ID == 2) {
			if (spell2.Ready()) {
				spell2.ResetCount();
				spell2.startCount();
				return 1;
			}
		}
		if (ID == 3) {
			if (spell3.Ready()) {
				spell3.ResetCount();
				spell3.startCount();
				return 1;
			}
		}
		return 0;
	}
};

