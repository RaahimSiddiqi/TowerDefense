#include "arrowTower.h"
#include "GameManager.h"
#include "ArrowBullet.h"


arrowTower::arrowTower() {
	name = "arrowTower";
	displayName = "Arrow Tower";
	sprite.setTexture(TextureManager::getInstance()->GetTexture("ArrowTowerSprites"));
	GameManager::getInstance()->file << "Created " << name << "Tower!" << endl;
	attack = 2;
	cooldown = 2;
	projectileSpeed = 20;
	cost = 400;
	value = 400;
	range.setRadius(250);

	rect = IntRect(0, 0, 55, 90);
	sprite.setTextureRect(rect);
	size = Vector2f(55, 90);
}

void arrowTower::Attack(Vector2f target, int direction, float speed) {
	if (cooldownFlag == 0 && builtFlag == 1) {
		GameManager::getInstance()->PlaySoundEffect("Crossbow");
		cooldownFlag = 1;
		clock.restart();

		Vector2f currentLoc = Vector2f(sprite.getPosition().x, sprite.getPosition().y);

		Vector2f offset = Vector2f(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
		
		double aimDirAngle = fireCalcAngle(target, currentLoc, offset);
		Vector2f pos = TowerAI(sprite.getPosition() + offset, target, this->projectileSpeed, speed, direction);
		GameManager::getInstance()->bullets.push_back(std::shared_ptr<Bullet>(new ArrowBullet(sprite.getPosition() + offset, pos, this->attack, aimDirAngle, projectileSpeed)));
	}
	//cout << "Under cooldown" << endl;
}

std::shared_ptr<Tower> arrowTower::getClassObject()
{
	std::shared_ptr<Tower> obj = std::make_shared<arrowTower>();
	return obj;
}

void arrowTower::Upgrade() {
	if (level < 3 && checkUpgradeCost()) {
		level += 1;

		rect.left += 55;
		
		
		if (level == 2) {
			attack += 1;
			range.setRadius(range.getRadius() + 30);
			value += (cost * level);
		}

		if (level == 3) {
			rect.left += 2;
			projectileSpeed += 4;
			cooldown -= 1;
			value += cost * level;
		}
		sprite.setTextureRect(rect);
	}
}
