#include "map.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameManager.h"
#include "TextureManager.h"
#include "DisplayMenu.h"


using namespace std;

Map* Map::instance = nullptr;

Map::Map(sf::RenderWindow& window) : Window(window) {
    castleTexture = TextureManager::getInstance()->GetTexture("Castle");
    castleSprite.setTexture(castleTexture);
    castleSprite.setScale(0.8, 0.8);
    backgroundTexture = TextureManager::getInstance()->GetTexture("GrassBackground");
    backgroundSprite.setPosition(0, 0);
    backgroundSprite.setTexture(backgroundTexture);
   
    CastleHP = HealthBar(100);
    CastleHP.setSize(Vector2f(100, 15));
    instance = this;

}

void Map::RenderFoilage() {
    for (int i = 0; i < 10; i++) {
        Vector2f pos;

        do {
            pos = Vector2f(rand() % 900, rand() % 600);

        } while (FoilageCheck(FloatRect(pos.x, pos.y, 80, 80)));
        foilage.push_back(Foilage(pos));
    }
}

void Map::RenderMap(int screen_width, int screen_height, int htiles, int vtiles, int border, Vector2f offset) {
    GameManager::getInstance()->file << "Rendering Map" << endl;
    this->Offset = offset;
    int tile_width = screen_width / htiles;
    int tile_height = screen_height / vtiles;
    _border = border;
    tile_size = Vector2f(tile_width, tile_height);

    //cout << tile_size.x << " . " << tile_size.y << endl;
    Color Black(0, 0, 0);
    //cout << "Htiles" << htiles << endl;
    //cout << "VTiles" << vtiles << endl;
    this->tiles.resize(htiles, vector<Tile>(vtiles));

    _htiles = htiles;
    _vtiles = vtiles;

    for (int i = 0; i < htiles; i++) {
        for (int j = 0; j < vtiles; j++) {
            this->tiles[i][j] = Tile(tile_size, Color::Green, border, Color::White);
            this->tiles[i][j].SetPosition(Vector2f(i * tile_size.x, j * tile_size.y) + offset);
            tiles[i][j].Draw(Window);
        }
    }
    Window.display();
}

void Map::UpdateMap(int htiles, int vtiles) {
    //Color grey(0x00818589);
    Color grey(100, 100, 100);

    for (int i = 0; i < htiles; i++) {
        for (int j = 0; j < vtiles; j++) {
            if (GameManager::getInstance()->tilemode == 1) {
                this->tiles[i][j].Draw(Window);
            }
        }
    }
    if (GameManager::getInstance()->tilemode == 0 && createPath == 1) {
        RenderBackground();
        RenderPath();
        drawFoilage();

    }
    RenderCastle();
}


void Map::onToggleGridMode() {
    for (int i = 0; i < _htiles; i++) {
        for (int j = 0; j < _vtiles; j++) {
            tiles[i][j].tile.setOutlineThickness(_border);
        }
    }
}

int Map::FoilageCheck(FloatRect rect) {
    for (int i = 0; i < _htiles; i++) {
        for (int j = 0; j < _vtiles; j++) {
            if (tiles[i][j].getID() == 1 || tiles[i][j].getID() == 2) {
                if (tiles[i][j].tile.getGlobalBounds().intersects(rect)) {
                    return 1;
                }
            }

        }
    }
    GameManager::getInstance()->file << "Rendering Foilage" << endl;
    return 0;
}



void Map::offToggleGridMode() {
    for (int i = 0; i < _htiles; i++) {
        for (int j = 0; j < _vtiles; j++) {
            tiles[i][j].tile.setOutlineThickness(0);
        }
    }
}

void Map::offToggleTileMode() {
    createPath = 1;
    GameManager::getInstance()->file << "Toggled off Tile Mode (MAP)" << endl;

    Color grey(100, 100, 100);
    this->pathtiles.resize(_htiles, vector<Tile>(_vtiles));

    for (int i = 0; i < _htiles; i++) {
        for (int j = 0; j < _vtiles; j++) {
            if (tiles[i][j].getID() == 1 || tiles[i][j].getID() == 2) {
                this->pathtiles[i][j] = Tile(tile_size, grey, 0, Color::Black);  
            }
            this->pathtiles[i][j].SetPosition(Vector2f(i * tile_size.x, j * tile_size.y) + Offset);
        }
    }
}

void Map::onToggleTileMode() {
    createPath = 0;
    GameManager::getInstance()->file << "Toggled On Tile Mode (MAP)" << endl;
    pathtiles.clear();
}

void Map::RenderCastle() {
    CastleHP.updateHealth(DisplayMenu::getInstance()->getHealth());
    castleSprite.setPosition(castleLocation + Offset);
    Window.draw(castleSprite);
    Window.draw(CastleHP.hbar);
}

void Map::RenderPath() {
    for (int i = 0; i < _htiles; i++) {
        for (int j = 0; j < _vtiles; j++) {
            pathtiles[i][j].Draw(Window);
        }
    }
}

void Map::drawFoilage() {
    if (foilage.size() == 0) {
        return;
    }

    for (int i = 0; i < foilage.size(); i++) {
        foilage[i].Draw(Window);
    }
}

void Map::RenderBackground() {
    Window.draw(backgroundSprite);
}

Map* Map::getInstance()
{
    return instance;
}

Map::~Map()
{
    if (instance == this)
    {
        instance = nullptr;
    }
}