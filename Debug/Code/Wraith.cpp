#include "Wraith.h"
#include "TextureManager.h"


Wraith::Wraith(int level) {
	shape.setSize(Vector2f(20, 20));
	sprite.setTexture(TextureManager::getInstance()->GetTexture("spritesheet3"));
	texturePos = IntRect(0, 0, 60, 49);
	sprite.setTextureRect(texturePos);
	spriteSheetWidth = 720;
	TextureRectHeight = 49;
	TextureRectWidth = 60; 
	sprite.setOrigin(TextureRectWidth / 2, TextureRectHeight / 2);


	
	if (level == 1) {
		speed = 4;
		health = 1;
		maxHealth = 1;
		attack = 1;
		armor = 0;
		money = 20;
	}
	else if (level == 2) {
		speed = 4;
		health = 2;
		maxHealth = 2;
		attack = 2;
		armor = 0;
		money = 30;
	}
	else if (level == 3) {
		speed = 8;
		health = 4;
		maxHealth = 4;
		attack = 3;
		armor = 0;
		money = 50;
	}

	name = "wraith";
	info = "Fast Flying Ghost";
	healthBar = HealthBar(health);
	tooltip.AddText("NAME: " + name);
	tooltip.AddText("INFO: " + info);
	tooltip.AddText("ATTACK: " + to_string(attack));
	tooltip.AddText("HEALTH: " + to_string(health));
	tooltip.AddText("ARMOR: " + to_string(armor));
}