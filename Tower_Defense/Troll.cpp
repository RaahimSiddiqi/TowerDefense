#include "Troll.h"
#include "TextureManager.h"

Troll::Troll(int level) {
	shape.setSize(Vector2f(30, 40));
	sprite.setTexture(TextureManager::getInstance()->GetTexture("spritesheet42"));
	texturePos = IntRect(0, 0, 116, 80);
	sprite.setTextureRect(texturePos);
	spriteSheetWidth = 1160;
	TextureRectHeight = 80;
	TextureRectWidth = 116;
	offset = 0;

	if (level == 1) {
		speed = 1;
		health = 25;
		maxHealth = 25;
		attack = 5;
		money = 40;
	}
	else if (level == 2) {
		speed = 1;
		health = 40;
		maxHealth = 40;
		attack = 5;
		money = 60;
	}
	else if (level == 3) {
		speed = 1;
		health = 60;
		maxHealth = 60;
		attack = 5;
		money = 100;
	}

	armor = 0;
	name = "troll";
	info = " Strong and Durable";
	healthBar = HealthBar(health);
	sprite.setOrigin(TextureRectWidth / 2, TextureRectHeight / 2);
	tooltip.AddText("NAME: " + name);
	tooltip.AddText("INFO: " + info);
	tooltip.AddText("ATTACK: " + to_string(attack));
	tooltip.AddText("HEALTH: " + to_string(health));
	tooltip.AddText("ARMOR: " + to_string(armor));
}