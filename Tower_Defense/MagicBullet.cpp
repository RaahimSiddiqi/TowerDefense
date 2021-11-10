#include "MagicBullet.h"


MagicBullet::MagicBullet(Vector2f location, Vector2f targetLocation, float attack, double angle, float speed) {
	_attack = attack;
	target = targetLocation;
	origin = location;
	this->speed = speed;
	shot.setPosition(location);
	shot.setFillColor(Color::Black);
	shot.setRadius(5.0f);
	this->type = "magic";
	tex = TextureManager::getInstance()->GetTexture("MagicShot");
	sprite.setTexture(tex);
	burst = TextureManager::getInstance()->GetTexture("magicExplosion");
	texBurstOn = 1;

	sprite.setOrigin(Vector2f(10, 20));
	sprite.setRotation(angle);
	sprite.setPosition(location);

	rect = IntRect(0, 0, 60, 61);
	size = Vector2f(60, 61);
}

int MagicBullet::PlayAnimation() {
	sprite.setRotation(0);
	sprite.setTexture(burst);

	sprite.setPosition(shot.getPosition().x - size.x / 2 + shot.getRadius(), shot.getPosition().y - size.y / 2 + shot.getRadius());
	//sprite.setPosition(shot.getPosition());
	sprite.setTextureRect(rect);

	if (timer.getElapsedTime().asMilliseconds() > 40) {
		rect.left += size.x;
		if (rect.left >= 960) {
			return 0;
		}
		sprite.setTextureRect(rect);
		timer.restart();
	}

	return 1;
}