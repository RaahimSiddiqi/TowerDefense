#include "Minotaur.h"
#include "TextureManager.h"

Minotaur::Minotaur(int level) {
	shape.setSize(Vector2f(30, 30));
	sprite.setTexture(TextureManager::getInstance()->GetTexture("spritesheet"));
	texturePos = IntRect(0, 0, 100, 68);
	sprite.setTextureRect(texturePos);
	spriteSheetWidth = 1800;
	TextureRectHeight = 68;
	TextureRectWidth = 100;

	if (level == 1) {
		attack = 1;
		health = 3;
		maxHealth = 3;
		speed = 2;
		armor = 0;
		money = 25;
	}
	else if (level == 2) {
		attack = 2;
		health = 5;
		maxHealth = 5;
		speed = 2;
		armor = 0;
		money = 40;
	}
	else if (level == 3) {
		attack = 3;
		health = 7;
		maxHealth = 7;
		speed = 3;
		armor = 0;
		money = 60;
	}

	name = "minotaur";
	info = "Half-Man Half Bull";
	healthBar = HealthBar(health);
	sprite.setOrigin(TextureRectWidth / 2, TextureRectHeight / 2);
	tooltip.AddText("NAME: " + name);
	tooltip.AddText("INFO: " + info);
	tooltip.AddText("ATTACK: " + to_string(attack));
	tooltip.AddText("HEALTH: " + to_string(health));
	tooltip.AddText("ARMOR: " + to_string(armor));
}


