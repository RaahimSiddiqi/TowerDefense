#include "MortarTower.h"
#include "GameManager.h"
#include "WindBullet.h"


MortarTower::MortarTower() {
	sprite.setTexture(TextureManager::getInstance()->GetTexture("MortarTower"));
	name = "mortarTower";
	displayName = "Mortar Tower";
	GameManager::getInstance()->file << "Created " << name << "Tower!" << endl;
	attack = 2;
	cooldown = 4;
	projectileSpeed = 20;
	cost = 250;
	value = 250;
	range.setRadius(100);

	rect = IntRect(0, 0, 68, 75);
	sprite.setTextureRect(rect);
	size = Vector2f(68, 75);
}

void MortarTower::Attack(Vector2f target, int direction, float speed) {
	if (cooldownFlag == 0 && builtFlag == 1) {
		cooldownFlag = 1;
		clock.restart();
		Vector2f currentLoc = Vector2f(sprite.getPosition().x, sprite.getPosition().y);

		Vector2f offset = Vector2f(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
		float aimDirAngle = fireCalcAngle(target, currentLoc, offset);

		Vector2f pos = TowerAI(sprite.getPosition() + offset, target, this->projectileSpeed, speed, direction);
		GameManager::getInstance()->bullets.push_back(std::shared_ptr<Bullet>(new WindBullet(sprite.getPosition() + offset, pos, this->attack, aimDirAngle, projectileSpeed)));
	}
	//cout << "Under cooldown" << endl;
}


void MortarTower::Upgrade() {
	if (level < 3 && checkUpgradeCost()) {
		level += 1;

		rect.left += 68;

		if (level == 2) {
			attack += 1;
			range.setRadius(range.getRadius() + 25);
			cooldown -= 1;
			value += cost * level;
		}

		if (level == 3) {
			attack += 1;
			range.setRadius(range.getRadius() + 25);
			value += cost * level;
		}
		sprite.setTextureRect(rect);
	}
}