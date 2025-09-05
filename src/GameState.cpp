#include "GameState.h"

GameState::GameState(sf::Vector2i _dimensions, int _numberOfMines)
{
    dimensions = _dimensions;
    numberOfMines = _numberOfMines;
    status = PLAYING;

    // This is the function that makes the gameboard
    for (int y = 0; y < dimensions.y; y++)
    {
        vector<Tile*> row;

        for (int x = 0; x < dimensions.x; x++)
        {
            Tile* tile = new Tile(sf::Vector2f(x, y), false);
            row.push_back(tile);
        }

        tiles.push_back(row);
    }

    // Use current time as rng seed
    srand(time(0));

    // Loop back through and change random tiles to bomb tiles
    for (int i = 0; i < numberOfMines; i++)
    {
        int rx = rand() % 25;
        int ry = rand() % 16;

        if (tiles[ry][rx]->getIsMine()) {
            i -= 1;
        }
        else {
            tiles[ry][rx]->setIsMine(true);
        }
    }
}

GameState::GameState(const char* filepath)
{
    int _numberOfMines = 0;

    ifstream boardFile(filepath);
    if (!boardFile.is_open()) {
        cerr << "Error opening the file!" << endl;
    }

    status = PLAYING;

    string line;
    int y = 0;

    while (getline(boardFile, line))
    {
        vector<Tile*> row;

        for (int x = 0; x < line.length(); x++)
        {
            if (line.at(x) == '1')  {
                // Add a bomb tile
                _numberOfMines += 1;
                cout << "1";
                Tile* bombTile = new Tile(sf::Vector2f(x, y), true);
                row.push_back(bombTile);
            }
            else {
                // Add a normal tile
                cout << "0";
                Tile* normalTile = new Tile(sf::Vector2f(x, y), false);
                row.push_back(normalTile);
            }
        }

        // Test 2 makes 4 endls because of the 4 blank lines in the file
        // (idk if this is how the file should be)
        cout << endl;
        tiles.push_back(row);
        y += 1;
    }

    boardFile.close();

    sf::Vector2i _dimensions(line.length(), y);

    dimensions = _dimensions;
    numberOfMines = _numberOfMines;
}

GameState::PlayStatus GameState::getPlayStatus()
{
    return status;
}

void GameState::setPlayStatus(PlayStatus _status)
{
    status = _status;
}

int GameState::getFlagCount()
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

int GameState::getMineCount()
{
    return numberOfMines;
}

sf::Vector2i GameState::getDimensions()
{
    return dimensions;
}

Tile* GameState::getTile(int x, int y)
{
    // Check if out of bounds (for use with finding neighbor tiles)
    if (x < 0 || x >= dimensions.y || y < 0 || y >= dimensions.x) {
        return nullptr;
    }
    return tiles[x][y];
}