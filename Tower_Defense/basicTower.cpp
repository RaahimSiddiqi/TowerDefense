#include "basicTower.h"
#include "MudBullet.h"
#include "GameManager.h"
#include "TextureManager.h"
#include <iostream>
using namespace std;

basicTower::basicTower() {
	sprite.setTexture(TextureManager::getInstance()->GetTexture("BasicTowerSprites"));
	name = "basicTower";
	displayName = "Basic Tower";
	GameManager::getInstance()->file << "Created " << name << endl;
	attack = 1;
	cooldown = 1;
	projectileSpeed = 8;
	cost = 200;
	value = 200;
	range.setRadius(100);

	rect = IntRect(0, 0, 52, 78);
	sprite.setTextureRect(rect);

	size = Vector2f(52, 78);
}

void basicTower::Attack(Vector2f target, int direction, float speed) {
	if (cooldownFlag == 0 && builtFlag == 1) {
		cooldownFlag = 1;
		clock.restart();

		Vector2f offset = Vector2f(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);

		Vector2f pos = TowerAI(sprite.getPosition() + offset, target, this->projectileSpeed, speed, direction);
		//GameManager::getInstance()->bullets.push_back(std::shared_ptr<Bullet>(new MudBullet(sprite.getPosition() + offset, target, this->attack, projectileSpeed)));
		GameManager::getInstance()->bullets.push_back(std::shared_ptr<Bullet>(new MudBullet(sprite.getPosition() + offset, pos, this->attack, projectileSpeed)));

	}
	//cout << "Under cooldown" << endl;
}

std::shared_ptr<Tower> basicTower::getClassObject()
{
	std::shared_ptr<Tower> obj = std::make_shared<basicTower>();

	return obj;
}

void basicTower::Upgrade() {
	if (level < 3 && checkUpgradeCost()) {
		level += 1;

		rect.left += 50;
		sprite.setTextureRect(rect);

		if (level == 2) {
			attack += 1;
			range.setRadius(range.getRadius() + 20);
			projectileSpeed += 2;
			value += cost * level;
		}

		if (level == 3) {
			attack += 1;
			range.setRadius(range.getRadius() + 10);
			projectileSpeed += 5;
			value += cost * level;
		}
	}
}