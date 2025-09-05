#pragma once

#include <SFML/Graphics.hpp>
#include <array>

#include "Toolbox.h"

using namespace std;

class Tile
{
    public: enum State { REVEALED, HIDDEN, FLAGGED, EXPLODED };
    State state;
    std::array<Tile*, 8> neighbors;
    sf::Vector2f location;
    bool isMine;

public:
    State getState();

    void setState(State _state);

    Tile(sf::Vector2f _position, bool _isMine);

    sf::Vector2f getLocation();

    bool getIsMine();

    void setIsMine(bool _isMine);

    std::array<Tile*, 8>& getNeighbors();

    void setNeighbors(std::array<Tile*, 8> _neighbors);

    void onClickLeft();

    void onClickRight();

    void draw();

protected:
    void revealNeighbors();
};