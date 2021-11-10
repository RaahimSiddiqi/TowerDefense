#pragma once
#include "TextureManager.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace sf;
using namespace std;

class CountDown
{
	Text count;
	int frames;
	Vector2f position;
	string text;
	int currCount;
	int running;
	int stopped;
	int ready;

public:

	CountDown(Vector2f pos, std::string num) {
		frames = 0;
		count.setFont(TextureManager::getInstance()->GetFont("Frostbite"));
		count.setCharacterSize(40);
		count.setString(num);
		count.setPosition(pos);
		position = pos;
		text = num;
		currCount = 0;
		stopped = 0;
		running = 0;
		ready = 0;
	}

	void ResetCount() {
		count.setString(text);
		stopped = 0;
		running = 0;
	}

	void stopCount() {
		stopped = 1;
		running = 0;
	}

	void startCount() {
		running = 1;
		stopped = 0;
		ready = 0;
	}

	int Update() {
		if (stopped == 1) return -1;

		frames += 1;
		if (frames == 60) {

			stringstream degree(count.getString());
			int x = 0;
			degree >> x;
			x -= 1;
			currCount = x;
			if (x == 0) {
				ready = 1;
				frames = 0;
				return 1;
			}
			count.setString(to_string(x));
			frames = 0;
		}
		//Draw(window);
		return 0;
	}


	void Draw(RenderWindow& window) {
		if (currCount >= 0 && Ready() != 1) {
			window.draw(count);
		}
	}

	int Ready() {
		return ready;
	}

};

