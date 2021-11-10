#pragma once
#include"SFML/Graphics.hpp"
#include <time.h>
#include<vector>
using namespace std;
using namespace sf;

class Particle
{
	sf::RectangleShape p;
	float length;
	sf::Vector2f spd;
	sf::Vector2f initialCoordinates;
	sf::RenderWindow* ptrWindow;
	Color color;
	int alpha;
	static int number;
	int cChange;

public:
	Particle(sf::RenderWindow& window, float l, Vector2f pos, Color c) {
		length = l;
		alpha = 220;
		cChange = static_cast<int>(c.g);
		ptrWindow = &window;
		p.setSize(Vector2f(length, length));
		spd.x = (rand() % 2) - 1;
		spd.y = (rand() % 3) - 3;
		color = c;

		initialCoordinates = pos;
		p.setPosition(pos);
		p.setFillColor(Color(static_cast<int>(color.r), cChange, static_cast<int>(color.b), alpha));
		//p.setFillColor(sf::Color(255, 255, 255, alpha));
		number++;
	}
	static int getNum() {
		return number;
	}

	static int setNum(int n) {
		return number = n;
	}

	static void decNum() {
		number -= 1;
	}

	void update() {
		if (length > 0)
			length -= 0.2;
		alpha -= 3;
		cChange += 6;
		p.setSize(Vector2f(length, length));

		initialCoordinates.x += spd.x;
		initialCoordinates.y += spd.y;

		p.setPosition(initialCoordinates);
		p.setFillColor(Color(static_cast<int>(color.r), cChange, static_cast<int>(color.b), alpha));
	}
	int getAlpha() {
		return this->alpha;
	}

	int getColor() {
		return this->cChange;
	}

	void draw() {
		this->ptrWindow->draw(p);
	}
};

