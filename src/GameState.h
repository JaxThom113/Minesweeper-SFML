#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <time.h>

using namespace std;

class Tile;

class GameState
{
    public: enum PlayStatus { WIN, LOSS, PLAYING };
    PlayStatus status;
    sf::Vector2i dimensions;
    int numberOfMines;
    vector<vector<Tile*>> tiles;

public:
    PlayStatus getPlayStatus();

    void setPlayStatus(PlayStatus _status);

    GameState(sf::Vector2i _dimensions = sf::Vector2i(25, 16), int _numberOfMines = 50);

    GameState(const char* filepath);

    int getFlagCount();

    int getMineCount();

    sf::Vector2i getDimensions();

    Tile* getTile(int x, int y);
};

#include "Tile.h"