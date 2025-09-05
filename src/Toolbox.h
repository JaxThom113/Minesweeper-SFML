#pragma once

#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "Button.h"

//class GameState;
//class Button;

using namespace std;

class Toolbox
{
    Toolbox(){};

public:
    sf::RenderWindow window; // SFML application window
    GameState* gameState; // Primary game state representation
    Button* debugButton; // Reveals mines in debug mode
    Button* newGameButton; // Resets / starts new game
    Button* testButton1; // Loads test board #1
    Button* testButton2; // Loads test board #2
    Button* testButton3; // Loads test board #3

    static Toolbox& getInstance()
    {
        static Toolbox single;
        return single;
    }
};