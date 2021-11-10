#include "poisonTower.h"
#include "GameManager.h"
#include "PoisonBullet.h"

poisonTower::poisonTower() {
	sprite.setTexture(TextureManager::getInstance()->GetTexture("PoisonTowerSprites"));
	name = "poisonTower";
	displayName = "Poison Tower";
	GameManager::getInstance()->file << "Created " << name << "Tower!" << endl;
	attack = 1;
	cooldown = 5;
	projectileSpeed = 20;
	duration = 3;
	cost = 500;
	value = 500;
	range.setRadius(80);

	rect = IntRect(0, 0, 51, 70);
	sprite.setTextureRect(rect);
	size = Vector2f(51, 70);
}

void poisonTower::Attack(Vector2f target, int direction, float speed) {
	if (cooldownFlag == 0 && builtFlag == 1) {
		cooldownFlag = 1;
		clock.restart();
		Vector2f currentLoc = Vector2f(sprite.getPosition().x, sprite.getPosition().y);

		Vector2f offset = Vector2f(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
		float aimDirAngle = fireCalcAngle(target, currentLoc, offset);

		Vector2f pos = TowerAI(sprite.getPosition() + offset, target, this->projectileSpeed, speed, direction);
		GameManager::getInstance()->bullets.push_back(std::shared_ptr<Bullet>(new PoisonBullet(sprite.getPosition() + offset, pos, this->attack, aimDirAngle, projectileSpeed)));
	}
	//cout << "Under cooldown" << endl;
}


void poisonTower::Upgrade() {
	if (level < 3 && checkUpgradeCost()) {
		level += 1;

		rect.left += 51;

		if (level == 2) {
			attack += 1;
			duration += 1;
			range.setRadius(range.getRadius() + 25);
			cooldown -= 1;
			value += cost * level;
		}

		if (level == 3) {
			attack += 1;
			range.setRadius(range.getRadius() + 25);
			duration += 1;
			cooldown -= 1;
			value += cost * level;
		}
		sprite.setTextureRect(rect);
	}
}