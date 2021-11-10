#include "Bullet.h"
#include "GameManager.h"


Bullet::Bullet() {

}

void Bullet::Update() {
	if ((shot.getPosition().x < 1000 && shot.getPosition().x > 0) && (shot.getPosition().y < 600 && shot.getPosition().y > 0)) {
		MoveToTarget();
		Draw();
	}
	else {
		cout << "MEM LEAK" << endl;
	}

	//sprite.setPosition(shot.getPosition().x - size.x / 2, shot.getPosition().y - size.y / 2);
	sprite.setPosition(shot.getPosition());
}

void Bullet::MoveToTarget() {
	Vector2f aimDir = target - origin;
	Vector2f aimDirNorm = aimDir / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
	Vector2f velocity = aimDirNorm * speed;

	shot.move(velocity);

}

void Bullet::Draw() {

	//GameManager::getInstance()->Window.draw(shot);
	GameManager::getInstance()->Window.draw(sprite);

}


Bullet::~Bullet() {
	//cout << "Bullet Destroyed" << endl;
}


float Bullet::getAttack() {
	return _attack;
}

int Bullet::PlayAnimation() {
	sprite.setTexture(tex);

	sprite.setPosition(shot.getPosition());
	sprite.setTextureRect(rect);

	if (timer.getElapsedTime().asMilliseconds() > 80) {
		rect.left += size.x;
		sprite.setTextureRect(rect);
		timer.restart();
		if (rect.left >= 480) {
			return 0;
		}
		
	}
	return 1;
}