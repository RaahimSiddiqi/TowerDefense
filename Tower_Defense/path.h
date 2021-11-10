#include <SFML/Window.hpp>
#include <math.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include "map.h"
#include <SFML/Graphics.hpp>

using namespace sf; 
using namespace std;
#pragma once


class Path {
private:
	Vector2f currpoint;
	

public:
	Vector2f startpoint;
	Vector2f endpoint;

	Path(int width, int height, int twists, int segments, int path);
	//void Path1(int width, int height, int twists, int segments);
	//void Path2(int width, int height, int twists, int segments);
	//void Path3(int width, int height, int twists, int segments);
	Path(int);

	void PathCreator(int[], int);
	void PathCreator(int[], int, int);

	void Up(int);
	void Down(int);
	void Forward(int);
	void Back(int);
};

