#include <SFML/Graphics.hpp>
#include <iostream>
#include "Enemy.h"
#include "map.h"
#include "GameManager.h"
#include <string>


Enemy::Enemy() {
	//shape.setSize(Vector2f(20, 20));
	//shape.setPosition(Vector2f(0, 300));
	TileLoc = Map::getInstance()->spawnPoint + Vector2f(abs(Map::getInstance()->Offset.x/20), abs(Map::getInstance()->Offset.y / 20));
	Offset = Vector2f(abs(Map::getInstance()->Offset.x / 20), abs(Map::getInstance()->Offset.y / 20));
	//healthBar = HealthBar(health);
	shape.setPosition(TileLoc.x  * 20, TileLoc.y * 20);
	setColor();
	determineDirection();
}

void Enemy::setColor() {
	if (health == 1.0) {
		shape.setFillColor(Color::Yellow);
	}
	else if (health == 2 || health == 3) {
		shape.setFillColor(Color::Green);
	}
	else if (health == 3 || health == 4) {
		shape.setFillColor(Color::Blue);
	}
	else if (health >= 5 and health <= 9) {
		shape.setFillColor(Color::Magenta);
	}
	else {
		shape.setFillColor(Color::Black);
	}
}

int Enemy::getDirection() {
	if (this->xdirection == 1) {
		return 0;
	}
	else if (this->ydirection == 1) {
		return 1;
	}
	else if (this->zdirection == 1) {
		return 2;
	}
	else if (this->minusxdirection == 1) {
		return 3;
	}
	return -1;
}

void Enemy::determineDirection() {
	//cout << "TileLoc (X): " << TileLoc.x << endl;
	//cout << "TileLoc (Y): " << TileLoc.y << endl;
	if (Map::getInstance()->tiles[TileLoc.x + 1 - Offset.x][TileLoc.y - Offset.y].getID() == 1 && minusxdirection != 1) {
		if (sprite.getScale().x == -1 && xdirection != 1) {
			sprite.scale(-1, 1);
		}

		xdirection = 1;
		ydirection = 0;
		zdirection = 0;
		minusxdirection = 0;
		//cout << "move forward" << endl;
	}

	else if (TileLoc.y > Offset.y && Map::getInstance()->tiles[TileLoc.x - Offset.x][TileLoc.y - Offset.y - 1].getID() == 1 && zdirection != 1) {
		if (sprite.getScale().x == -1 && ydirection != 1) {
			sprite.scale(-1, 1);
		}

		ydirection = 1;
		xdirection = 0;
		zdirection = 0;
		minusxdirection = 0;
	}
	else if (Map::getInstance()->tiles[TileLoc.x - Offset.x][TileLoc.y + 1 - Offset.y].getID() == 1 && ydirection != 1) {
		if (sprite.getScale().x == -1 && zdirection != 1) {
			sprite.scale(-1, 1);
		}

		//cout << "Move down" << endl;
		zdirection = 1;
		ydirection = 0;
		xdirection = 0;
		minusxdirection = 0;
		if (sprite.getScale().x == -1) {
			sprite.scale(-1, 1);
		}
	}
	else if (Map::getInstance()->tiles[TileLoc.x - 1 - Offset.x][TileLoc.y - Offset.y].getID() == 1 && xdirection != 1) {
		//cout << "Move back" << endl;
		if (minusxdirection != 1) {
			sprite.scale(-1, 1);
		}

		zdirection = 0;
		ydirection = 0;
		xdirection = 0;
		minusxdirection = 1;
	}
}


void Enemy::Move(float speed) {
	if (frozen) {
		return;
	}

	if (xdirection == 1) {
		shape.move(Vector2f(speed, 0));
	}
	else if (ydirection == 1) {
		shape.move(Vector2f(0, -speed));
	}
	else if (zdirection == 1) {
		shape.move(Vector2f(0, speed));
	}
	else if (minusxdirection == 1) {
		shape.move(Vector2f(-speed, 0));
	}

	for (int i = 0; i < speed; i++) {
		if (speed >= 1) {
			TilesCovered++;
		}
		else {
			TilesCovered += speed;
		}
		
		if (TilesCovered >= 20) {
			TilesCovered = 0;
			if (xdirection == 1) {
				TileLoc += Vector2f(1, 0);
			}
			else if (ydirection == 1) {
				TileLoc += Vector2f(0, -1);
			}
			else if (zdirection == 1) {
				TileLoc += Vector2f(0, 1);
			}
			else if (minusxdirection == 1) {
				TileLoc += Vector2f(-1, 0);
			}

			//cout << "Change Direction" << endl;
			determineDirection();
		}
	}
}

void Enemy::Update(Vector2f MousePos) {
	sprite.setPosition(shape.getPosition() + Vector2f(10, 10));
	Effects();
	healthBar.updateHealth(this->health);

	if (animationClock.getElapsedTime().asMilliseconds() >= 80) {
		animationClock.restart();
		NextFrame();
	}

	Move(speed);
	GameManager::getInstance()->Window.draw(sprite);
	healthBar.hbar.setPosition(shape.getPosition().x, shape.getPosition().y - 30);
	GameManager::getInstance()->Window.draw(healthBar.hbar);

	if (sprite.getGlobalBounds().contains(MousePos)) {
		UpdateToolTip();
		tooltip.Update(GameManager::getInstance()->Window);
	}

}


int Enemy::takeDamage(int attack) {

	if (attack <= armor) {
		return 0;
	}
	this->health -= attack - armor;

	GameManager::getInstance()->dmgEffects.push_back(DamageEffect(attack - armor, shape.getPosition()));
	GameManager::getInstance()->PlaySoundEffect("LightImpact");
	//cout << name << " took damage. " << "Current health " << health << endl;
	setColor();
	return 1;
}

int Enemy::takeDamage(int attack, Color color) {

	if (attack <= armor) {
		GameManager::getInstance()->dmgEffects.push_back(DamageEffect(0, shape.getPosition(), color));
		return 0;
	}
	this->health -= attack - armor;
	GameManager::getInstance()->dmgEffects.push_back(DamageEffect(attack - armor, shape.getPosition(), color));
	GameManager::getInstance()->PlaySoundEffect("LightImpact");
	//cout << name << " took damage. " << "Current health " << health << endl;
	setColor();
	return 1;
}

int Enemy::takeDamage(int attack, Color color, string type) {

	if (type == "magic" || type == "poison") {
		this->health -= attack;
		GameManager::getInstance()->dmgEffects.push_back(DamageEffect(attack, shape.getPosition(), color));
	}
	else {
		if (attack <= armor) {
			GameManager::getInstance()->dmgEffects.push_back(DamageEffect(0, shape.getPosition(), color));
			return 0;
		}
		this->health -= attack - armor;
		GameManager::getInstance()->dmgEffects.push_back(DamageEffect(attack - armor, shape.getPosition(), color));
	}

	GameManager::getInstance()->PlaySoundEffect("LightImpact");
	setColor();
	return 1;
}

void Enemy::NextFrame() {
	if (!frozen) {
		texturePos.left += TextureRectWidth + offset;
		if (texturePos.left >= spriteSheetWidth) {
			texturePos.left = 0;
		}
		sprite.setTextureRect(texturePos);
	}
}

float Enemy::getSpeed() {
	return this->speed;
}

void Enemy::Effects() {
	vector<Effect>::iterator i;
	for (i = this->effects.begin(); i != this->effects.end();) {
	
		if (i->ID == 1) // Poison
		{
			if (i->turn > 0 && i->timer.getElapsedTime().asMilliseconds() > 2000) {
				this->takeDamage(1, Color::Green, "poison");
				i->timer.restart();
				i->turn -= 1;
				++i;
			}
			else if (i->turn == 0) {
				i = effects.erase(i);
				if (effects.size() == 0) {
					this->healthBar.hbar.setFillColor(Color::Red);
				}
				else {
					if (effects[0].ID == 1) {
						healthBar.hbar.setFillColor(Color::Green);
					}
					else if (effects[0].ID == 2) {
						healthBar.hbar.setFillColor(Color::Cyan);
					}
					else {
						healthBar.hbar.setFillColor(Color::Red);
					}
				}
				UpdateToolTip();
				sprite.setColor(Color(255, 255, 255, 255));
			}
			else {
				++i;
			}
		}
		else if (i->ID == 2) { // Freeze
			if (i->timer.getElapsedTime().asMilliseconds() > i->duration) {
				this->speed *= 2.f;			
				i = effects.erase(i);
				if (effects.size() == 0) {
					this->healthBar.hbar.setFillColor(Color::Red);
				}
				else {
					if (effects[0].ID == 1) {
						healthBar.hbar.setFillColor(Color::Green);
					}
					else if (effects[0].ID == 2) {
						healthBar.hbar.setFillColor(Color::Cyan);
					}
					else {
						healthBar.hbar.setFillColor(Color::Red);
					}
				}
				UpdateToolTip();
				sprite.setColor(Color(255, 255, 255, 255));
			}
			else {
				++i;
			}
		}
		else if (i->ID == 3) { // KnockBack
			if (i->turn > 0 && i->timer.getElapsedTime().asMilliseconds() > i->duration) {
	
				if (xdirection == 1) {
					if (Map::getInstance()->tiles[TileLoc.x - 1][TileLoc.y].getID() == 1) {
						shape.setPosition(shape.getPosition() - Vector2f(20, 0));
						TileLoc.x -= 1;
					}
				}
				if (ydirection == 1) {
					if (Map::getInstance()->tiles[TileLoc.x][TileLoc.y - 1].getID() == 1) {
						shape.setPosition(shape.getPosition() - Vector2f(0, -20));
						TileLoc.y += 1;
					}
				}
				if (zdirection == 1) {
					if (Map::getInstance()->tiles[TileLoc.x][TileLoc.y + 1].getID() == 1) {
						shape.setPosition(shape.getPosition() - Vector2f(0, +20));
						TileLoc.y -= 1;
					}
				}
				if (minusxdirection == 1) {
					if (Map::getInstance()->tiles[TileLoc.x + 1][TileLoc.y].getID() == 1) {
						shape.setPosition(shape.getPosition() + Vector2f(20, 0));
						TileLoc.x += 1;
					}
				}
				i->turn -= 1;
				i->timer.restart();
			}
			else if (i->turn == 0) {  
				i = effects.erase(i);
				UpdateToolTip();
				sprite.setColor(Color(255, 255, 255, 255));
			}
			else {
				++i;
			}
		}
		else if (i->ID == 4) {  // Time Stop
			if (i->timer.getElapsedTime().asMilliseconds() > i->duration) {
				this->frozen = 0;
				i = effects.erase(i);
			}
			else {
				++i;
			}
		}
		else
		{
			++i;
		}
	}
}

void Enemy::poisionEffect(float attack = 1, int turn = 3) {
	Effect poison;
	poison.ID = 1;
	poison.name = "poison";
	poison.turn = turn;
	poison.attack = attack;
	this->healthBar.hbar.setFillColor(Color::Green);
	effects.push_back(poison);
	//sprite.setColor(Color(0, 255, 0, 128));
	tooltip.AddText("AFFECTED BY POISON");
}

void Enemy::frostEffect() {
	Effect frost;
	frost.ID = 2;
	frost.name = "frost";
	frost.duration = 5000;
	frost.turn = 0;
	speed = speed / 2.f;
	this->healthBar.hbar.setFillColor(Color::Cyan);
	//sprite.setColor(Color(0, 0, 255, 255));
	tooltip.AddText("AFFECTED BY FROST");
	effects.push_back(frost);
}
\

void Enemy::KnockBackEffect() {

	Effect knockBack;
	knockBack.ID = 3;
	knockBack.turn = 4;
	knockBack.duration = 100;
	effects.push_back(knockBack);
}

void Enemy::frostEffect(int duration) {
	Effect frost;
	frost.ID = 2;
	frost.name = "frost";
	frost.turn = 0;
	frost.duration = duration;
	speed = speed / 2.f;
	this->healthBar.hbar.setFillColor(Color::Cyan);
	sprite.setColor(Color(0, 0, 255, 128));
	tooltip.AddText("AFFECTED BY FROST");
	effects.push_back(frost);
}

void Enemy::frozenEffect(int duration) {
	Effect frozen;
	frozen.ID = 4;
	frozen.name = "frozen";
	frozen.turn = 0;
	frozen.duration = duration;
	tooltip.AddText("FROZEN");
	this->frozen = 1;
	effects.push_back(frozen);
}

void Enemy::ApplyEffect(int ID, float atk, int duration) {
	if (ID == 1) {
		poisionEffect(atk);
	}
	if (ID == 2) {
		frostEffect(duration);
	}
	if (ID == 3) {
		KnockBackEffect();
	}
	if (ID == 4) {
		frozenEffect(duration);
	}
}


void Enemy::UpdateToolTip() {
	tooltip.Clear();
	tooltip.AddText("NAME: " + name);
	tooltip.AddText("INFO: " + info);
	tooltip.AddText("ATTACK: " + to_string(attack));
	tooltip.AddText("HEALTH: " + to_string(health));
	tooltip.AddText("ARMOR: " + to_string(armor));

	for (unsigned int i = 0; i < effects.size(); i++) {
		if (i >= 2) {
			break;
		}
		tooltip.AddText("Affected by: " + effects[i].name);
	}
}