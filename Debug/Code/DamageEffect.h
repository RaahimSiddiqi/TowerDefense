#pragma once
#include "TextureManager.h"
#include <string>
#include <random>

using namespace std;

class DamageEffect
{
private:
	Text text;
	int frames = 0;
	Color color;

public:
	DamageEffect(int dmg, Vector2f Position) {
		srand(time(0));
		text.setFont(TextureManager::getInstance()->GetFont("Neuropol"));
		text.setString(to_string(dmg));
		text.setPosition(Position);
		text.setCharacterSize(17 + (dmg - 3));
		color = Color::White;
		color.a = 255;
	}

	DamageEffect(int dmg, Vector2f Position, Color c) {
		text.setFont(TextureManager::getInstance()->GetFont("Neuropol"));
		text.setString(to_string(dmg));
		text.setPosition(Position);
		text.setCharacterSize(17 + (dmg - 3));
		color = c;
	}

	void Update(RenderWindow& window) {
		if (frames % 10 == 0) {
			text.setPosition(text.getPosition() + Vector2f(0, -1));
		}
		window.draw(text);
	
		frames += 1;
		text.setFillColor(Color(static_cast<int>(color.r), static_cast<int>(color.g), static_cast<int>(color.b), static_cast<int>(color.a - (frames * 4))));
	}

	int getFrame() { return frames; };
};

