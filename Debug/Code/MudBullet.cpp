#include "MudBullet.h"


MudBullet::MudBullet(Vector2f location, Vector2f targetLocation, float attack, float speed) {
	_attack = attack;
	target = targetLocation;
	origin = location;
	this->speed = speed;
	this->type = "normal";
	shot.setPosition(location);
	shot.setFillColor(Color::Black);
	shot.setRadius(5.0f);


	tex = TextureManager::getInstance()->GetTexture("Shot");
	sprite.setTexture(tex);
	sprite.setPosition(location);
}

int MudBullet::PlayAnimation() {
	return 1;
}