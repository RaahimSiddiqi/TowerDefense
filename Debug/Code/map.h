#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <math.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include "HealthBar.h"
#include "Tile.h"
#include "Foilage.h"

using namespace sf;
using namespace std;

class Map {
    static Map* instance;
    Texture castleTexture;
    Texture backgroundTexture;
    int _border;
    int createPath = 0;
    sf::RenderWindow& Window;

public:
    vector<Foilage> foilage;
    vector< vector<Tile> > tiles;
    vector< vector<Tile> > pathtiles;
    int id = 0;
    
    Sprite castleSprite;

    Sprite backgroundSprite;
    Vector2f Position;
    Vector2f tile_size;
    Vector2f spawnPoint;
    Vector2f Offset;
    void drawFoilage();
    int FoilageCheck(FloatRect);
    void RenderFoilage();

    Map(sf::RenderWindow& window);
    int _htiles;
    int _vtiles; 
   
    Map();
    ~Map();

    void RenderMap(int screen_width, int screen_height, int htiles, int vtiles, int border, Vector2f offset);
    Vector2f castleLocation;

    void onToggleTileMode();
    void onToggleGridMode();
    void offToggleTileMode();
    void offToggleGridMode();
    void UpdateMap(int htiles, int vtiles);
    void RenderCastle();
    void RenderBackground();
    void RenderPath();
    HealthBar CastleHP;
    static Map* getInstance();
};



/*
    int RenderMap(int screen_width, int screen_height, int htiles, int vtiles) : m_window(window) {
        int tile_width = screen_width / htiles;
        int tile_height = screen_height / vtiles;

        Vector2f tile_size = Vector2f(tile_width, tile_height);

        for (int i = 0; i < tile_size.x; i++) {
            for (int j = 0; i < tile_size.y; j++) {
                RectangleShape tile = RectangleShape(tile_size);
                window->draw(tile);
            }
        }
    }

*/