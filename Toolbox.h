#pragma once

#include <SFML/Graphics.hpp>


using namespace std;

// Forward declare so that Tile::draw() doesn't get circular dependency error
class GameState;
class Button;

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

        static Toolbox& getInstance()
        {
            static Toolbox single;
            return single;
        }
};