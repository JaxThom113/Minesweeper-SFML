#include "Tile.h"

using namespace std;

Tile::Tile(sf::Vector2f _position, bool _isMine)
{
    location = _position;
    isMine = _isMine;
    state = HIDDEN;
}

sf::Vector2f Tile::getLocation()
{
    // Location is the position in the grid
    return location;
}

void Tile::setState(State _state)
{
    state = _state;
}

Tile::State Tile::getState()
{
    return state;
}

bool Tile::getIsMine()
{
    return isMine;
}

void Tile::setIsMine(bool _isMine)
{
    isMine = _isMine;
}

std::array<Tile*, 8>& Tile::getNeighbors()
{
    std::array<Tile*, 8> adjTiles;

    adjTiles[0] = Toolbox::getInstance().gameState->getTile(location.y-1, location.x+1);
    adjTiles[1] = Toolbox::getInstance().gameState->getTile(location.y, location.x+1);
    adjTiles[2] = Toolbox::getInstance().gameState->getTile(location.y+1, location.x+1);
    adjTiles[3] = Toolbox::getInstance().gameState->getTile(location.y-1, location.x);
    adjTiles[4] = Toolbox::getInstance().gameState->getTile(location.y+1, location.x);
    adjTiles[5] = Toolbox::getInstance().gameState->getTile(location.y-1, location.x-1);
    adjTiles[6] = Toolbox::getInstance().gameState->getTile(location.y, location.x-1);
    adjTiles[7] = Toolbox::getInstance().gameState->getTile(location.y+1, location.x-1);

    neighbors = adjTiles;

    return neighbors;
}

void Tile::setNeighbors(std::array<Tile*, 8> _neighbors)
{
    neighbors = _neighbors;
}

void Tile::onClickLeft()
{
    // Only allow left click if not flagged
    if (this->state != FLAGGED) {
        if (isMine) {
            state = EXPLODED;
            // Lose state
            Toolbox::getInstance().gameState->setPlayStatus(GameState::LOSS);
        }
        else {
            state = REVEALED;
            revealNeighbors();
        }
    }
}

void Tile::onClickRight()
{
    // Toggle between HIDDEN and FLAGGED
    switch (this->state)
    {
        case HIDDEN:
            state = FLAGGED;
            break;

        case FLAGGED:
            state = HIDDEN;
            break;
    }

    if (Toolbox::getInstance().gameState->getMineCount() - Toolbox::getInstance().gameState->getFlagCount() == 0)
    {
        // Win state
        Toolbox::getInstance().gameState->setPlayStatus(GameState::WIN);
    }
}

void Tile::draw()
{
    switch (this->state)
    {
        case REVEALED: {
            sf::Image revealedTileImage;
            sf::Texture revealedTileTexture;
            sf::Sprite revealedTileSprite;
            revealedTileImage.loadFromFile("images/tile_revealed.png");
            revealedTileTexture.loadFromImage(revealedTileImage);
            revealedTileSprite.setTexture(revealedTileTexture);

            revealedTileSprite.setPosition(sf::Vector2f(this->getLocation().x * 32, this->getLocation().y * 32));
            Toolbox::getInstance().window.draw(revealedTileSprite);

            int adjMines = 0;

            for (Tile* tile : this->getNeighbors())
            {
                if (tile != nullptr && tile->getIsMine()) {
                    adjMines += 1;
                }
            }

            if (adjMines > 0)
            {
                sf::Image numImage;
                sf::Texture numTexture;
                sf::Sprite numSprite;

                switch (adjMines)
                {
                    case 1: numImage.loadFromFile("images/number_1.png"); break;
                    case 2: numImage.loadFromFile("images/number_2.png"); break;
                    case 3: numImage.loadFromFile("images/number_3.png"); break;
                    case 4: numImage.loadFromFile("images/number_4.png"); break;
                    case 5: numImage.loadFromFile("images/number_5.png"); break;
                    case 6: numImage.loadFromFile("images/number_6.png"); break;
                    case 7: numImage.loadFromFile("images/number_7.png"); break;
                    case 8: numImage.loadFromFile("images/number_8.png"); break;
                }

                numTexture.loadFromImage(numImage);
                numSprite.setTexture(numTexture);

                numSprite.setPosition(sf::Vector2f(this->getLocation().x * 32, this->getLocation().y * 32));
                Toolbox::getInstance().window.draw(numSprite);
            }

            break;
        }

        case HIDDEN: {
            sf::Image hiddenTileImage;
            sf::Texture hiddenTileTexture;
            sf::Sprite hiddenTileSprite;
            hiddenTileImage.loadFromFile("images/tile_hidden.png");
            hiddenTileTexture.loadFromImage(hiddenTileImage);
            hiddenTileSprite.setTexture(hiddenTileTexture);

            hiddenTileSprite.setPosition(sf::Vector2f(this->getLocation().x * 32, this->getLocation().y * 32));
            Toolbox::getInstance().window.draw(hiddenTileSprite);

            break;
        }

        case FLAGGED: {
            sf::Image hiddenTileImage;
            sf::Texture hiddenTileTexture;
            sf::Sprite hiddenTileSprite;
            hiddenTileImage.loadFromFile("images/tile_hidden.png");
            hiddenTileTexture.loadFromImage(hiddenTileImage);
            hiddenTileSprite.setTexture(hiddenTileTexture);

            hiddenTileSprite.setPosition(sf::Vector2f(this->getLocation().x * 32, this->getLocation().y * 32));
            Toolbox::getInstance().window.draw(hiddenTileSprite);

            sf::Image flagImage;
            sf::Texture flagTexture;
            sf::Sprite flagSprite;
            flagImage.loadFromFile("images/flag.png");
            flagTexture.loadFromImage(flagImage);
            flagSprite.setTexture(flagTexture);

            flagSprite.setPosition(sf::Vector2f(this->getLocation().x * 32, this->getLocation().y * 32));
            Toolbox::getInstance().window.draw(flagSprite);

            break;
        }

        case EXPLODED: {
            sf::Image revealedTileImage;
            sf::Texture revealedTileTexture;
            sf::Sprite revealedTileSprite;
            revealedTileImage.loadFromFile("images/tile_revealed.png");
            revealedTileTexture.loadFromImage(revealedTileImage);
            revealedTileSprite.setTexture(revealedTileTexture);

            revealedTileSprite.setPosition(sf::Vector2f(this->getLocation().x * 32, this->getLocation().y * 32));
            Toolbox::getInstance().window.draw(revealedTileSprite);

            sf::Image mineImage;
            sf::Texture mineTexture;
            sf::Sprite mineSprite;
            mineImage.loadFromFile("images/mine.png");
            mineTexture.loadFromImage(mineImage);
            mineSprite.setTexture(mineTexture);

            mineSprite.setPosition(sf::Vector2f(this->getLocation().x * 32, this->getLocation().y * 32));
            Toolbox::getInstance().window.draw(mineSprite);

            break;
        }
    }
}

void Tile::revealNeighbors()
{
    // See how many neighbors have mines
    int adjMines = 0;
    for (Tile* tile : this->getNeighbors())
    {
        if (tile != nullptr && tile->getIsMine()) {
            adjMines += 1;
        }
    }

    // If none of the neighbors have mines, reveal them all
    if (adjMines == 0)
    {
        for (Tile* tile : this->getNeighbors())
        {
            if (tile != nullptr && tile->getState() == HIDDEN)
            {
                tile->setState(REVEALED);
                tile->revealNeighbors();
            }
        }
    }
}