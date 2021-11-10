#include "BlueMinotaur.h"
#include "TextureManager.h"


BlueMinotaur::BlueMinotaur(int level) {
	shape.setSize(Vector2f(30, 30));
	sprite.setTexture(TextureManager::getInstance()->GetTexture("spritesheet2"));
	texturePos = IntRect(0, 0, 100, 68);
	sprite.setTextureRect(texturePos);
	spriteSheetWidth = 1800;
	TextureRectHeight = 68;
	TextureRectWidth = 100;

	if (level == 1) {
		money = 35;
		health = 5;
		maxHealth = 5;
		attack = 2;
		speed = 2;
		armor = 1;
	}
	else if (level == 2) {
		money = 50;
		health = 6;
		maxHealth = 6;
		attack = 2;
		speed = 2;
		armor = 2;
	}
	else if (level == 3) {
		money = 70;
		health = 7;
		maxHealth = 7;
		attack = 3;
		speed = 2;
		armor = 3;
	}

	name = "blueminotaur";
	info = "Armored Minotaur";
	sprite.setOrigin(TextureRectWidth / 2, TextureRectHeight / 2);
	healthBar = HealthBar(health);

	tooltip.AddText("NAME: " + name);
	tooltip.AddText("INFO: " + info);
	tooltip.AddText("ATTACK: " + to_string(attack));
	tooltip.AddText("HEALTH: " + to_string(health));
	tooltip.AddText("ARMOR: " + to_string(armor));
}