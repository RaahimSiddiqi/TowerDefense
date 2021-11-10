#include "WindBullet.h"
#include "GameManager.h"
#include <iostream>

WindBullet::WindBullet(Vector2f location, Vector2f targetLocation, float attack, double angle, float speed) {
	_attack = attack;
	target = targetLocation;
	origin = location;
	this->effect = 3;
	this->speed = speed;
	shot.setPosition(location);
	shot.setFillColor(Color::Black);
	shot.setRadius(5.0f);
	sprite.setPosition(location);

	tex = TextureManager::getInstance()->GetTexture("CannonBall");
	sprite.setTexture(tex);
	burst = TextureManager::getInstance()->GetTexture("WindBlast");
	texBurstOn = 1;

	sprite.setOrigin(Vector2f(shot.getGlobalBounds().width / 2, shot.getGlobalBounds().height / 2));
	sprite.setRotation(angle);
	sprite.setPosition(location);

	rect = IntRect(0, 0, 150, 120);
	size = Vector2f(150, 120);

}

int WindBullet::PlayAnimation() {
	sprite.setRotation(0);
	sprite.setTexture(burst);

	sprite.setPosition(shot.getPosition().x - size.x / 2 + shot.getRadius(), shot.getPosition().y - size.y / 2 + shot.getRadius());
	sprite.setTextureRect(rect);


	if (timer.getElapsedTime().asMilliseconds() > 40) {
		if (rect.left == 150) {
			GameManager::getInstance()->PlaySoundEffect("WindBlast", 25);
		}

		rect.left += 150;
		if (rect.left >= 1200) {
			return 0;
			rect.left = 0;
		}
		sprite.setTextureRect(rect);
		timer.restart();
	}

	return 1;
}