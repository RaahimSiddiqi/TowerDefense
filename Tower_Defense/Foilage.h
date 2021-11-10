#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureManager.h"
#include <random>
#include <time.h>

using namespace std;
using namespace sf;

class Foilage
{
	Sprite sprite;
public:
	Foilage(Vector2f pos) {

		int choice = rand() % 2;
		if (choice == 0) {
			sprite.setTexture(TextureManager::getInstance()->GetTexture("Trees"));
			int x = rand() % 4;
			int y = rand() % 4;
			sprite.setTextureRect(IntRect(x * 80, y * 80, 80, 80));
		}
		else if (choice == 1) {
			sprite.setTexture(TextureManager::getInstance()->GetTexture("rocks"));
			int x = rand() % 3;
			int y = rand() % 3;
			sprite.setTextureRect(IntRect(x * 60, y * 50, 60, 50));
		}
		sprite.setPosition(pos);
	}

	FloatRect getBounds() {
		return sprite.getGlobalBounds();
	}

	void Draw(RenderWindow& window) {
		window.draw(sprite);
	}

};

