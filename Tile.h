#pragma once

#include <SFML/Graphics.hpp>
#include <array>

#include "Toolbox.h"

using namespace std;

class Tile
{
    public: enum State { REVEALED, HIDDEN, FLAGGED, EXPLODED };
    State state = HIDDEN;
    std::array<Tile*, 8> neighbors;
    sf::Vector2f location;
    bool isMine;

    public:
        State getState()
        {
            return this->state;
        }

        void setState(State _state)
        {
            this->state = _state;
        }

        Tile(sf::Vector2f _position, bool _isMine)
        {
            this->location = _position;
            this->isMine = _isMine;
        }

        sf::Vector2f getLocation()
        {
            // Location is the position in the grid
            return this->location;
        }
        
        bool getIsMine()
        {
            return this->isMine;
        }

        void setIsMine(bool _isMine)
        {
            this->isMine = _isMine;
        }

        std::array<Tile*, 8>& getNeighbors()
        {
            return this->neighbors;
        }

        void setNeighbors(std::array<Tile*, 8> _neighbors)
        {
            this->neighbors = _neighbors;
        }

        void onClickLeft()
        {
            // Only allow left click if not flagged
            if (!this->state == FLAGGED) {
                if (this->isMine)
                {
                    this->state = EXPLODED;
                }
                else 
                {
                    this->state = REVEALED;
                }
            }
        }

        void onClickRight()
        {
            // Toggle between HIDDEN and FLAGGED
            switch (this->state)
            {
                case HIDDEN:
                    this->state = FLAGGED;
                    break;

                case FLAGGED:
                    this->state = HIDDEN;
                    break;
            }
        }

        void draw()
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
                    cout << "Before" << endl;
                    Toolbox::getInstance().window.draw(revealedTileSprite);
                    cout << "After" << endl;

                    break;
                }
                    
                case HIDDEN: {
                    cout << "Bolts" << endl;
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
                    break;
                }
                    
                case EXPLODED: {
                    break;
                }
            }
        }
    
    protected:
        void revealNeighbors()
        {
            return;
        }
};