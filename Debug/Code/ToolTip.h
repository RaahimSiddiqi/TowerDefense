#pragma once
#include "TextureManager.h"

using namespace sf;
using namespace std;


class ToolTip
{
	Clock timer;
	Vector2f Position;
	vector <Text> texts;
	Sprite sprite;
	RectangleShape rect;

public:
	ToolTip() { 
		Position = Vector2f(720, 20);
		sprite.setPosition(Position);
		sprite.setTexture(TextureManager::getInstance()->GetTexture("ToolTip"));
		rect.setPosition(Position);
	};
	ToolTip(Vector2f Pos) : Position(Pos) {
		sprite.setPosition(Position);
		rect.setPosition(Position);
	};

	void SetPosition(Vector2f pos) { Position = pos; };

	void Update(RenderWindow& window) {
		//window.draw(rect);
		window.draw(sprite);
		for (unsigned int i = 0; i < texts.size(); i++) {
			texts[i].setPosition(rect.getPosition() + Vector2f(8, 8) + Vector2f(0, i * 20));
			window.draw(texts[i]);
		}
	}
	void AddText(string str) {
		Text text;
		texts.push_back(text);
		texts[texts.size() - 1].setCharacterSize(20);
		texts[texts.size() - 1].setString(str);
		texts[texts.size() - 1].setFont(TextureManager::getInstance()->GetFont("Frostbite"));
	}

	void AddText(string str, int char_size) {
		Text text;
		texts.push_back(text);
		texts[texts.size() - 1].setCharacterSize(char_size);
		texts[texts.size() - 1].setString(str);
		texts[texts.size() - 1].setFont(TextureManager::getInstance()->GetFont("Frostbite"));
	}

	void Clear() {
		texts.clear();
	}
};

