#include <SFML/Graphics.hpp>
#include <iostream>
#include "tower.h"
#include "TextureManager.h"
#include "map.h"
#include "DisplayMenu.h"
#include "GameManager.h"



Tower::Tower() {
	range.setFillColor(Color::Transparent);
	range.setOutlineColor(Color::Red);
	range.setOutlineThickness(2);
	range.setRadius(100);
	followMouse();
	GameManager::getInstance()->toggleTileMode();
	ArrowTexture = TextureManager::getInstance()->GetTexture("SelectionArrow");
	A1.setTexture(ArrowTexture);
	A2.setTexture(ArrowTexture);
}

void Tower::setFollowing(int value) {
	following = value;
	
}

void displayDetails(shared_ptr<Tower>& t) {
	cout << "Tower Name: " << t->name << endl;
	cout << "Tower Attack: " << t->attack << endl;
	cout << "Tower Cooldown: " << t->cooldown << endl;
	cout << "Tower Range: " << t->range.getRadius() << endl;
}

void Tower::followMouse() {
	TileContact(); // Checks for tile collisions
	Vector2f mousePos = Vector2f(Mouse::getPosition(GameManager::getInstance()->Window).x, Mouse::getPosition(GameManager::getInstance()->Window).y);
	sprite.setPosition(mousePos.x - size.x /2 , mousePos.y - size.y / 2);

	if (Mouse::isButtonPressed(Mouse::Left) and mousePos.y < 600) {
		removeContactColoring(); // remove coloring for a moment to check whether it can be built
		if (checkTiles() == 0) {
			following = 0;
			builtFlag = 1;
			Color lightgrey(140, 140, 140);
			ContactTileColoring(lightgrey);
			GameManager::getInstance()->PlaySoundEffect("TowerConstruct", 25);
			GameManager::getInstance()->toggleTileMode();
			FoilageCollisionCheck();
		}
		else {
			cout << "Space Occupied!" << endl;
			TileContact(); // re-anble coloring if check failed
		}
	}
	removeContactTiles();
}

void Tower::FoilageCollisionCheck() {
	vector<Foilage>::iterator i;
	for (i = Map::getInstance()->foilage.begin(); i != Map::getInstance()->foilage.end();) {
		if ((i->getBounds().intersects(sprite.getGlobalBounds())))
		{
			i = Map::getInstance()->foilage.erase(i);
		}
		else
		{
			++i;
		}
	}
}


void Tower::TileContact() {
	Color lightgrey(140, 140, 140);
	Color lightergrey(180, 180, 180);
	Color grey(100, 100, 100);

	for (unsigned int i = 0; i < Map::getInstance()->tiles.size(); i++) {
		for (unsigned int j = 0; j < Map::getInstance()->tiles[0].size(); j++) {
			if (sprite.getGlobalBounds().intersects(Map::getInstance()->tiles[i][j].tile.getGlobalBounds())) {
				if (Map::getInstance()->tiles[i][j].tile.getFillColor() != Color::Red && Map::getInstance()->tiles[i][j].tile.getFillColor() != grey && Map::getInstance()->tiles[i][j].tile.getFillColor() != lightgrey) {
					Map::getInstance()->tiles[i][j].tile.setFillColor(lightgrey);
					contactTiles.emplace_back(&Map::getInstance()->tiles[i][j]);
				}
			}
		}
	}
}

void Tower::removeContactTiles() {
	vector<Tile*>::iterator i;
	for (i = contactTiles.begin(); i != contactTiles.end();) {
		if (!((*i)->tile.getGlobalBounds().intersects(sprite.getGlobalBounds())))
		{
			(*i)->tile.setFillColor(Color::Green);
			i = contactTiles.erase(i);
		}
		else
		{
			++i;
		}
	}
}

void Tower::removeContactColoring() {
	for (unsigned int z = 0; z < contactTiles.size(); z++) {
		if (contactTiles[z] != NULL) 
			contactTiles[z]->tile.setFillColor(Color::Green);
	}
}

void Tower::DestroyTower() {
	ContactTileColoring(Color::Green);
	builtFlag = 0;
	GameManager::getInstance()->removeTower();
}

void Tower::Update() {
	if (following == 1) {
		followMouse();
	}

	time = clock.getElapsedTime();
	if (time.asSeconds() > cooldown) {
		cooldownFlag = 0;
	}
	else {
		cooldownFlag = 1;
	}
	if (selectedEnemy != nullptr) {

		if (selectedEnemy->getHealth() <= 0) {
			selectedEnemy = nullptr;
		}
	}

	if (selectedEnemy != nullptr && range.getGlobalBounds().intersects(selectedEnemy->sprite.getGlobalBounds())) {
		Attack(selectedEnemy->shape.getPosition() + (selectedEnemy->shape.getSize() / 2.f), selectedEnemy->getDirection(), selectedEnemy->getSpeed());
	}

	Draw();
}

void Tower::Draw() {
	range.setPosition(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width / 2 - range.getRadius(), sprite.getGlobalBounds().top + sprite.getGlobalBounds().height / 2 -range.getRadius());
	if (GameManager::getInstance()->gridmode == 1) {
		GameManager::getInstance()->Window.draw(range);
	}
	GameManager::getInstance()->Window.draw(sprite);

	if (isSelected) {
		A1.setPosition(sprite.getPosition() + Vector2f(-sprite.getTextureRect().width / 2, 0)+  Vector2f(A1.getGlobalBounds().width/2, -A1.getTextureRect().height) + Vector2f(5, 0));

		GameManager::getInstance()->Window.draw(A1);

		if (selectedEnemy != nullptr) {
			//A2.setPosition(selectedEnemy->sprite.getPosition() + Vector2f(0, -selectedEnemy->sprite.getGlobalBounds().width /2) + Vector2f(-A2.getTextureRect().width/2,0));
			A2.setPosition(selectedEnemy->sprite.getPosition() + Vector2f(0, -selectedEnemy->sprite.getGlobalBounds().height / 2) + Vector2f(-A2.getTextureRect().width / 2, -A2.getTextureRect().height) + Vector2f(0, 2));
			GameManager::getInstance()->Window.draw(A2);
		}
	}
}

int Tower::ContactTileColoring(Color color) {
	int flag = 0;
	for (unsigned int i = 0; i < Map::getInstance()->tiles.size(); i++) {
		for (unsigned int j = 0; j < Map::getInstance()->tiles[0].size(); j++) {
			if (sprite.getGlobalBounds().intersects(Map::getInstance()->tiles[i][j].tile.getGlobalBounds())) {
				Map::getInstance()->tiles[i][j].tile.setFillColor(color);
			}
		}
	}

	return flag;
}

int Tower::checkTiles() {
	int flag = 0;
	Color grey(100, 100, 100);
	Color lightgrey(140, 140, 140);

	for (unsigned int i = 0; i < Map::getInstance()->tiles.size(); i++) {
		for (unsigned int j = 0; j < Map::getInstance()->tiles[0].size(); j++) {
			if (sprite.getGlobalBounds().intersects(Map::getInstance()->tiles[i][j].tile.getGlobalBounds())) {
				if (grey == Map::getInstance()->tiles[i][j].tile.getFillColor() || Color::Red == Map::getInstance()->tiles[i][j].tile.getFillColor() || lightgrey == Map::getInstance()->tiles[i][j].tile.getFillColor()) {
					flag = 1;
				}
			}
		}
	}

	return flag;
}

void Tower::Attack(Vector2f target, int direction, float speed) {
	cout << "NULL Tower Attack" << endl;
}


void Tower::setAttack(float TowerAttack) {
	attack = TowerAttack;
}

double Tower::fireCalcAngle(Vector2f v1, Vector2f v2, Vector2f v3 = Vector2f(0,0)) {
	Vector2f aimDir = v1 - (v2 + v3);
	double aimDirAngle = atan(aimDir.y / aimDir.x) * (180 / 3.142);

	if (aimDir.y < 0) {
		if (aimDir.x < 0) {
			aimDirAngle = -90 + aimDirAngle;
		}
		else if (aimDir.x > 0) {
			aimDirAngle += 90;
		}
	}
	else if (aimDir.y > 0) {
		if (aimDir.x < 0) {
			aimDirAngle = 270 + aimDirAngle;
		}
		else if (aimDir.x > 0) {
			aimDirAngle = 90 + aimDirAngle;
		}
	}
	return aimDirAngle;
}


Vector2f Tower::TowerAI(Vector2f v1, Vector2f v2, float s1, float s2, int dir) {
	// Find Magnitude
	Vector2f res = v2 - v1; // resultant
	float mag = sqrt(pow(res.x, 2)+ pow(res.y, 2)); // magnitude
	Vector2f aimDirNorm = res / mag;   // Unit Vector
	Vector2f velocity = aimDirNorm * s1;   // Velocity Components

	Vector2f targetPos = v2;
	s2 *= 5;

	if (dir == 0) {
		targetPos.x += ((s2 / s1) * 20) + (((mag+20) - 120)/(mag)) * 20;
	}
	else if (dir == 1) {
		targetPos.y -= ((s2 / s1) * 20) + (((mag+20) - 120) / (mag)) * 20;
	}
	else if (dir == 2) {
		targetPos.y += ((s2 / s1) * 20) + (((mag+20) - 120) / (mag)) * 20;
	}
	else if (dir == 3) {
		targetPos.x -= ((s2 / s1) * 20) + (((mag+20) - 120) / (mag)) * 20;
	}
	
	return targetPos;

}

float Tower::getAttack() {
	return attack;
}

float Tower::getSpeed() {
	return ( 1.0f / cooldown ) * 8;
}

float Tower::getRange() {
	return range.getRadius();
}

int Tower::getLevel() {
	return level;
}

int Tower::getCost() {
	return cost;
}

int Tower::getValue() {
	return value;
}

float Tower::getProjectileSpeed() {
	return projectileSpeed;
}


void Tower::Upgrade() {

	if (level < 3 && checkUpgradeCost())  {
		level += 1;
	}
}

int Tower::checkCost() {
	if (DisplayMenu::getInstance()->getMoney() < cost) {
		cout << "Not enough Money" << endl;
		return 0;
	}
	else {
		DisplayMenu::getInstance()->setMoney(DisplayMenu::getInstance()->getMoney() - cost);
	}
	return 1;
}

int Tower::checkUpgradeCost() {
	if (DisplayMenu::getInstance()->getMoney() >= (cost * (level + 1))) {
		DisplayMenu::getInstance()->setMoney(DisplayMenu::getInstance()->getMoney() - (cost * (level + 1)));
		return 1;
	}
	else {
		return 0;
	}
}


Tower::~Tower() {
	cout << name <<  " Destroyed Tower" << endl;
}

float Tower::getRefund() {
	return value / 2.f;
}

Tower& Tower::getInstance() {
	return *this;
}