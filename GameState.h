#pragma once

#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "BombTile.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib> 
#include <time.h> 

using namespace std;

class GameState
{
    public: enum PlayStatus { WIN, LOSS, PLAYING };
    PlayStatus status = PLAYING;
    sf::Vector2i dimensions;
    int numberOfMines;
    vector<vector<Tile*>> tiles;

    public:
        PlayStatus getPlayStatus()
        {
            return this->status;
        }

        void setPlayStatus(PlayStatus _status)
        {
            this->status = _status; // Code breaks here
        }

        GameState(sf::Vector2i _dimensions = sf::Vector2i(25, 16), int _numberOfMines = 50)
        {
            this->dimensions = _dimensions;
            this->numberOfMines = _numberOfMines;

            // This is the function that makes the gameboard
            for (int y = 0; y < dimensions.y; y++)
            {
                vector<Tile*> row;

                for (int x = 0; x < dimensions.x; x++)
                {   
                    Tile tile(sf::Vector2f(x, y), false);
                    row.push_back(&tile);
                }   

                tiles.push_back(row);
            }

            // Loop back through an change random tiles to bomb tiles
            // for (int i = 0; i < numberOfMines; i++)
            // {
            //     // Use current time as rng seed
            //     srand(time(0));
                
            //     int rx = rand() % 25;
            //     int ry = rand() % 16;

            //     if (tiles[ry][rx]->getIsMine()) 
            //         i -= 1;
            //     else 
            //         tiles[ry][rx]->setIsMine(true);
            // }   
        }

        GameState(const char* filepath)
        {
            ifstream boardFile(filepath);
            string line;

            int i = 0;

            while (getline(boardFile, line)) 
            { 
                vector<Tile*> row;

                for (int k = 0; k < line.length(); k++)
                {
                    if (line.at(k) == '1')  {
                        // Add a bomb tile
                        Tile bombTile(sf::Vector2f(k, i), true);
                        row.push_back(&bombTile);
                    }
                    else {
                        // Add a normal tile
                        Tile normalTile(sf::Vector2f(k, i), false);
                        row.push_back(&normalTile);
                    }
                }

                tiles.push_back(row);
                i += 1;
            } 

            boardFile.close();
        }

        int getFlagCount()
        {
            int flags = 0;

            for (vector<Tile*> row : tiles)
            {
                for (Tile* tile : row)
                {   
                    if (tile->getState() == Tile::FLAGGED) {
                        flags += 1;
                    }
                }
            }

            return flags;
        }

        int getMineCount()
        {
            return this->numberOfMines;
        }

        sf::Vector2i getDimensions()
        {
            return this->dimensions;
        }

        Tile* getTile(int x, int y)
        {   
            return this->tiles[x][y];
        }
};