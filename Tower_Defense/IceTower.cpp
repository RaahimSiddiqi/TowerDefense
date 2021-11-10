#include "IceTower.h"
#include "GameManager.h"
#include "IceBullet.h"

IceTower::IceTower() {
	name = "IceTowerSprites";
	displayName = "Ice Tower";
	sprite.setTexture(TextureManager::getInstance()->GetTexture("IceTowerSprites"));
	GameManager::getInstance()->file << "Created " << name << "Tower!" << endl;

	duration = 6000;
	attack = 1;
	cooldown = 5;
	projectileSpeed = 20;
	cost = 500;
	value = 500;
	range.setRadius(100);

	rect = IntRect(0, 0, 53, 98);
	sprite.setTextureRect(rect);

	size = Vector2f(53, 98);
}

void IceTower::Attack(Vector2f target, int direction, float speed) {
	if (cooldownFlag == 0 && builtFlag == 1) {
		cooldownFlag = 1;
		clock.restart();
		//cout << "ArrowTower Attack" << endl;
		Vector2f currentLoc = Vector2f(sprite.getPosition().x, sprite.getPosition().y);
		Vector2f offset = Vector2f(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);

		float aimDirAngle = fireCalcAngle(target, currentLoc, offset);
		Vector2f pos = TowerAI(sprite.getPosition() + offset, target, this->projectileSpeed, speed, direction);
		GameManager::getInstance()->bullets.push_back(std::shared_ptr<Bullet>(new IceBullet(sprite.getPosition() + offset, pos, this->attack, projectileSpeed, duration, aimDirAngle)));
	}
	//cout << "Under cooldown" << endl;

}


void IceTower::Upgrade() {
	if (level < 3 && checkUpgradeCost()) {
		level += 1;

		rect.left += 53;
		sprite.setTextureRect(rect);

		if (level == 2) {
			range.setRadius(range.getRadius() + 25);
			projectileSpeed += 5;
			cooldown -= 1;
			duration += 2000;
			value += (cost * level);
		}

		if (level == 3) {
			range.setRadius(range.getRadius() + 25);
			cooldown -= 1;
			duration += 2000;
			projectileSpeed += 5;
			value += cost * level;
		}
	}
}
