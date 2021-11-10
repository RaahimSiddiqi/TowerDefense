#include "Tile.h"
#include "TextureManager.h"

Tile::Tile(Vector2f tile_size, Color tile_color, float border_size, Color border_color) {
	this->ID = 0;
	this->interactLevel = 0;
	tile.setFillColor(tile_color);
	tile.setSize(tile_size);
	tile.setOutlineThickness(border_size);
	tile.setOutlineColor(border_color);
	//t = TextureManager::getInstance()->GetTexture("TileTexture");
	//s.setTexture(t);
	//s.setTextureRect(IntRect(0, 0, 20, 20));
}

Tile::Tile() {
	ID = -1;
	interactLevel = -1;
}

void Tile::Draw(RenderWindow& window) {
	window.draw(tile);
}

void Tile::SetPosition(Vector2f Pos) {
	tile.setPosition(Pos);
	//s.setPosition(Pos);
}

void Tile::setID(int id) {
	this->ID = id;
	if (id == 0) {
		this->tile.setFillColor(Color::Green);
	}
	else if (id == 1) {
		this->tile.setFillColor(Color::Red);
	}
	else if (id == 2) {
		Color grey(100, 100, 100);
		this->tile.setFillColor(grey);
	}
	else if (id == 3) {
		Color lightgrey(140, 140, 140);
		this->tile.setFillColor(lightgrey);
	}
}

int Tile::getID() {
	return this->ID;
}


void Tile::setInteractLevel(int lvl) {
	this->interactLevel = lvl;
}

int Tile::getInteractLevel() {
	return this->interactLevel;
}
