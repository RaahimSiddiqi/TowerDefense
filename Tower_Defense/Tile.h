#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Tile
{
	int ID;
	int interactLevel;

public:
	Tile();
	Tile(Vector2f, Color, float, Color);
	RectangleShape tile;
	Sprite s;
	Texture t;
	void Draw(RenderWindow&);
	void SetPosition(Vector2f);


	// ID (Represents the kind of tile it is)
	// 0 -> Free Tile (Green)
	// 1 -> Main Path Tile
	// 2 -> Side Path Tile
	// 3 -> Occupied by Construct (e.g Tower)
	// 4 -> Foilage
	
	// interactLevel
	// 0 -> Free Tile
	// 

	int getID();
	int getInteractLevel();
	void setID(int);
	void setInteractLevel(int);
	void LoadTexture();
	FloatRect getGlobalBounds() {
		return tile.getGlobalBounds();
	}
};

