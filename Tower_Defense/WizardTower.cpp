#include "WizardTower.h"
#include "TextureManager.h"
#include "GameManager.h"
#include "FireBullet.h"

wizardTower::wizardTower() {
	sprite.setTexture(TextureManager::getInstance()->GetTexture("WizardTower"));
	name = "wizardTower";
	displayName = "Wizard Tower";
	GameManager::getInstance()->file << "Created " << name << "Tower!" << endl;

	attack = 5;
	cooldown = 5;
	projectileSpeed = 10;
	cost = 500;
	value = 500;
	range.setRadius(130);

	rect = IntRect(0, 0, 41, 90);
	sprite.setTextureRect(rect);
	size = Vector2f(41, 90);
}

void wizardTower::Attack(Vector2f target, int direction, float speed) {
	if (cooldownFlag == 0 && builtFlag == 1) {
		GameManager::getInstance()->PlaySoundEffect("explosion");
		cooldownFlag = 1;
		clock.restart();
		Vector2f currentLoc = Vector2f(sprite.getPosition().x, sprite.getPosition().y);

		Vector2f offset = Vector2f(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
		float aimDirAngle = fireCalcAngle(target, currentLoc, offset);

		Vector2f pos = TowerAI(sprite.getPosition() + offset, target, this->projectileSpeed, speed, direction);
		GameManager::getInstance()->bullets.push_back(std::shared_ptr<Bullet>(new FireBullet(sprite.getPosition() + offset, pos, this->attack, aimDirAngle, projectileSpeed)));
	}
	//cout << "Under cooldown" << endl;
}


void wizardTower::Upgrade() {
	if (level < 3 && checkUpgradeCost()) {
		level += 1;

		rect.left += 41;

		if (level == 2) {
			attack += 2;
			range.setRadius(range.getRadius() + 30);
			projectileSpeed += 5;
			cooldown -= 2;
			value += cost * level;
			rect.left -= 3;
		}

		if (level == 3) {
			attack += 3;
			range.setRadius(range.getRadius() + 20);
			cooldown -= 1;
			value += cost * level;
			rect.left += 3;
		}
		sprite.setTextureRect(rect);
	}
}