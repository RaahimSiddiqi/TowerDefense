#include "PoisonBullet.h"
#include <iostream>

PoisonBullet::PoisonBullet(Vector2f location, Vector2f targetLocation, float attack, double angle, float speed) {
	_attack = attack;
	target = targetLocation;
	origin = location;
	this->effect = 1;
	this->speed = speed;
	shot.setPosition(location);
	shot.setFillColor(Color::Black);
	shot.setRadius(5.0f);
	sprite.setPosition(location);
	this->type = "poison";
	tex = TextureManager::getInstance()->GetTexture("PoisonBottle");
	sprite.setTexture(tex);
	burst = TextureManager::getInstance()->GetTexture("PoisionBulletAnimations");
	texBurstOn = 1;

	sprite.setOrigin(Vector2f(shot.getGlobalBounds().width/2, shot.getGlobalBounds().height / 2));
	sprite.setRotation(angle);
	sprite.setPosition(location);

	rect = IntRect(0, 0, 142, 142);
	size = Vector2f(142, 142);

}

int PoisonBullet::PlayAnimation() {
	sprite.setRotation(0);
	sprite.setTexture(burst);

	sprite.setPosition(shot.getPosition().x - size.x / 2 + shot.getRadius(), shot.getPosition().y - size.y / 2 + shot.getRadius());
	sprite.setTextureRect(rect);

	
	if (timer.getElapsedTime().asMilliseconds() > 20) {
		rect.left += 142;
		if (rect.left >= 1278) {
			return 0;
			rect.left = 0;
		}
		sprite.setTextureRect(rect);
		timer.restart();
	}

	return 1;
}