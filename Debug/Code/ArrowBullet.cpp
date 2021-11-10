#include "ArrowBullet.h"


ArrowBullet::ArrowBullet(Vector2f location, Vector2f targetLocation, float attack, double angle, float speed) {
	_attack = attack;
	target = targetLocation;
	origin = location;
	this->speed = speed;
	shot.setPosition(location);
	shot.setFillColor(Color::Black);
	shot.setRadius(5.0f);
	tex = TextureManager::getInstance()->GetTexture("Arrow");
	this->type = "pierce";

	sprite.setPosition(location);
	sprite.setOrigin(Vector2f(5, 20));
	sprite.setRotation(static_cast<float>(angle));
	sprite.setTexture(tex);

}

int ArrowBullet::PlayAnimation() {

	return 1;
}