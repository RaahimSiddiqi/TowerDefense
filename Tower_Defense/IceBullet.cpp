#include "IceBullet.h"
#include "GameManager.h"
#include <iostream>
using namespace std;

IceBullet::IceBullet(Vector2f location, Vector2f targetLocation, float attack, float speed, float duration, double angle) {
	_attack = attack;
	target = targetLocation;
	origin = location;
	this->speed = speed;
	this->effect = 2;
	this->duration = duration;
	this->type = "frost";
	shot.setPosition(location);
	shot.setFillColor(Color::Black);
	shot.setRadius(5.0f);
	texBurstOn = 1;
	tex = TextureManager::getInstance()->GetTexture("IceBolt");
	sprite.setTexture(tex);
	burst = TextureManager::getInstance()->GetTexture("IceBulletAnimations");
	sprite.setPosition(location);
	sprite.setRotation(angle);
	rect = IntRect(0, 0, 60, 60);
	size = Vector2f(60, 60);
}

int IceBullet::PlayAnimation() {
	sprite.setRotation(0);
	sprite.setTexture(burst);

	sprite.setPosition(shot.getPosition().x - size.x / 2 + shot.getRadius(), shot.getPosition().y - size.y / 2 + shot.getRadius());
	//sprite.setPosition(shot.getPosition());
	sprite.setTextureRect(rect);

	if (timer.getElapsedTime().asMilliseconds() > 70) {
		if (rect.left == 60) {
			GameManager::getInstance()->PlaySoundEffect("Freeze", 25);
		}

		rect.left += 60;
		if (rect.left >= 480) {
			return 0;
		}
		sprite.setTextureRect(rect);
		timer.restart();
	}
	return 1;
}