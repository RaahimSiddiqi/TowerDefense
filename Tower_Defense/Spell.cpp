#include "Spell.h"
#include "GameManager.h"
#include "TextureManager.h"

Spell::Spell(Vector2f targetPos) {
	cout << "created" << endl;
	sprite.setTexture(TextureManager::getInstance()->GetTexture("LightningAnimations"));
	spritesheetsize = Vector2f(918, 302);
	spritesize = Vector2f(102, 302);
	sprite.setTextureRect(rect);
	sprite.scale(0.35, 0.35);
	turns = 2;
	damage = 5;
	active = 1;
	duration = 30;

	Attack(targetPos);
}

Spell::Spell(Vector2f pos, int value) {
	cout << "created" << endl;
	sprite.setTexture(TextureManager::getInstance()->GetTexture("hearts"));
	spritesheetsize = Vector2f(1200, 120);
	spritesize = Vector2f(120, 120);
	sprite.setTextureRect(rect);
	sprite.setPosition(pos - Vector2f(20, 10));
	active = 1;
	turns = 0;
	duration = 50;
}

Spell::Spell(Vector2f pos, float a) {
	cout << "created" << endl;
	sprite.setTexture(TextureManager::getInstance()->GetTexture("WhiteFlash"));
	spritesheetsize = Vector2f(1100, 98);
	spritesize = Vector2f(100, 98);
	sprite.setTextureRect(rect);
	sprite.setPosition(pos.x - spritesize.x/2, pos.y - spritesize.y/2);
	active = 1;
	turns = 0;
	duration = 30;
}

int Spell::Update() {
	Animate();
	if (active == 1) {
		GameManager::getInstance()->Window.draw(sprite);
		return 1;
	}
	else {
		return 0;
	}
}

void Spell::Animate() {
	if (clock.getElapsedTime().asMilliseconds() > duration) {
		rect.left += spritesize.x;
		if (rect.left >= spritesheetsize.x) {
			rect.left = 0;
			if (turns > 1) {
				turns -= 1;
			}
			else {
				active = 0;
			}
		}
		sprite.setTextureRect(rect);
		clock.restart();
	}
}


void Spell::Attack(Vector2f targetPos) {
	targetPos.y -= 65;
	targetPos.x += 10;
	sprite.setPosition(targetPos);

}