#include "magicTower.h"
#include "TextureManager.h"
#include "MagicBullet.h"
#include "GameManager.h"

magicTower::magicTower() {
	sprite.setTexture(TextureManager::getInstance()->GetTexture("MagicTowerSprites"));
	name = "magicTower";
	displayName = "Magic Tower";
	GameManager::getInstance()->file << "Created " << name << "Tower!" << endl;
	attack = 3;
	cooldown = 3;
	projectileSpeed = 12;
	cost = 300;
	value = 300;
	range.setRadius(130);

	rect = IntRect(0, 0, 46, 90);
	sprite.setTextureRect(rect);
	size = Vector2f(46, 90);
}

void magicTower::Attack(Vector2f target, int direction, float speed) {
	if (cooldownFlag == 0 && builtFlag == 1) {
		cooldownFlag = 1;
		clock.restart();
		Vector2f currentLoc = Vector2f(sprite.getPosition().x, sprite.getPosition().y);

		Vector2f offset = Vector2f(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
		float aimDirAngle = fireCalcAngle(target, currentLoc, offset);

		Vector2f pos = TowerAI(sprite.getPosition() + offset, target, this->projectileSpeed, speed, direction);
		GameManager::getInstance()->bullets.push_back(std::shared_ptr<Bullet>(new MagicBullet(sprite.getPosition() + offset, pos, this->attack, aimDirAngle, projectileSpeed)));
	}
	//cout << "Under cooldown" << endl;
}

std::shared_ptr<Tower> magicTower::getClassObject()
{
	std::shared_ptr<Tower> obj = std::make_shared<magicTower>();

	return obj;
}


void magicTower::Upgrade() {
	if (level < 3 && checkUpgradeCost()) {
		level += 1;

		rect.left += 46;

		if (level == 2) {
			attack += 1;
			range.setRadius(range.getRadius() + 20);
			cooldown -= 1;
			value += cost * level;
		}

		if (level == 3) {
			attack += 1;
			range.setRadius(range.getRadius() + 20);
			projectileSpeed += 3;
			cooldown -= 1;
			value += cost * level;
		}
		sprite.setTextureRect(rect);
	}
}