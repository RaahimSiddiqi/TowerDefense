#include "FireBullet.h"
#include <iostream>

FireBullet::FireBullet(Vector2f location, Vector2f targetLocation, float attack, double angle, float speed) {
	_attack = attack;
	target = targetLocation;
	origin = location;
	this->speed = speed;
	shot.setPosition(location);
	shot.setFillColor(Color::Black);
	shot.setRadius(6.0f);
	texBurstOn = 1;
	this->type = "fire";

	tex = TextureManager::getInstance()->GetTexture("FireShot");
	sprite.setTexture(tex);

	sprite.setOrigin(Vector2f(15, 29));
	sprite.setRotation(angle);
	sprite.setPosition(location);

	burst = TextureManager::getInstance()->GetTexture("Explosion");
	rect = IntRect(0, 0, 120, 120);
	size = Vector2f(120, 120);

}

int FireBullet::PlayAnimation() {
	sprite.setRotation(0);
	sprite.setTexture(burst);

	sprite.setPosition(shot.getPosition().x - size.x / 2 + shot.getRadius(), shot.getPosition().y - size.y / 2 + shot.getRadius());
	//sprite.setPosition(shot.getPosition().x - size.x / 2, shot.getPosition().y - size.y / 2);
	//sprite.setPosition(shot.getPosition());
	sprite.setTextureRect(rect);

	if (timer.getElapsedTime().asMilliseconds() > 70) {
		rect.left += 120;
		if (rect.left >= 976) {
			return 0;
		}
		sprite.setTextureRect(rect);
		timer.restart();
	}

	return 1;
}