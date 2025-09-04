#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "Toolbox.h"
#include "GameState.h"
#include "Button.h"

using namespace std;

Toolbox &toolbox = Toolbox::getInstance();
bool debug = false;

// I wished this worked (white square problem)
// sf::Sprite getSprite(string filepath)
// {
//     sf::Image image;
//     image.loadFromFile(filepath);
//     sf::Texture texture;
//     texture.loadFromImage(image);
//     sf::Sprite sprite;
//     sprite.setTexture(texture);

//     return sprite;
// }

void toggleDebugMode()
{
    if (debug) {
        debug = false;
    }
    else {
        debug = true;
    }
    cout << "Debug toggled: " << debug << endl;
}

bool getDebugMode()
{
    return debug;   
}

void loadTest1()
{
    //toolbox.gameState = new GameState("boards/testboard1.brd");
    cout << "Test 1 loaded" << endl;
}

void loadTest2()
{
    //toolbox.gameState = new GameState("boards/testboard2.brd");
    cout << "Test 2 loaded" << endl;
}

void restart()
{
    if (debug) {
        debug = false;
    }

    //toolbox.gameState = new GameState();
    //toolbox.gameState->setPlayStatus(GameState::PlayStatus::PLAYING); 

    GameState newGame(sf::Vector2i(25, 16), 50);
    newGame.setPlayStatus(GameState::PLAYING);
    toolbox.gameState = &newGame;

    // cout << toolbox.gameState->getDimensions().x << ", " << toolbox.gameState->getDimensions().y << endl;

    cout << "Game reset!" << endl;
}

void render()
{
    return;
}

int launch()
{   
    restart();

    // sf::RenderWindow newWindow(sf::VideoMode(800, 600), "P4 - Minesweeper, Jaxon Kundrat");
    // toolbox.window = newWindow;

    toolbox.window.create(sf::VideoMode(800, 600), "P4 - Minesweeper, Jaxon Kundrat"); 
    // PlayStatus gets set to 800
    // getDimensions.x gets set to 600
    // getDimensions.y gets set to 1452041671

    //cout << toolbox.gameState->getDimensions().x << ", " << toolbox.gameState->getDimensions().y << endl;

    bool clicking = false;

    // This is the game loop (while window is open)
    while (toolbox.window.isOpen())
    {
        sf::Event event;
        while (toolbox.window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed: {
                    // If the x is pressed, close the window
                    toolbox.window.close();
                    break;
                }
                    
                case sf::Event::MouseButtonPressed: {
                    // LMB clicked
                    if (event.mouseButton.button == sf::Mouse::Left) 
                    {
                        if ((*toolbox.newGameButton->getSprite()).getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && !clicking) 
                        {
                            // New game button clicked
                            toolbox.newGameButton->onClick();
                        }
                        if((*toolbox.debugButton->getSprite()).getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && !clicking)
                        {
                            // Clicking debug button
                            toolbox.debugButton->onClick();
                        }
                        if((*toolbox.testButton1->getSprite()).getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && !clicking)
                        {
                            // Clicking debug button
                            toolbox.testButton1->onClick();
                        }
                        if((*toolbox.testButton2->getSprite()).getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && !clicking)
                        {
                            // Clicking debug button
                            toolbox.testButton2->onClick();
                        }
                        
                        clicking = true;
                    }

                    // RMB clicked
                    if (event.mouseButton.button == sf::Mouse::Right) 
                    {   
                        clicking = true;
                    }

                    break;
                }
                
                default: {
                    // Mouse up
                    clicking = false;
                    break;
                }
            }
        }

        //toolbox.window.clear(sf::Color::White);

        sf::Image smileyImage;
        sf::Texture smileyTexture;
        sf::Sprite smileySprite;
        smileyImage.loadFromFile("images/face_happy.png");
        smileyTexture.loadFromImage(smileyImage);
        smileySprite.setTexture(smileyTexture);

        Button smileyButton(sf::Vector2f((toolbox.window.getSize().x/2) - 32, 512), restart);
        smileyButton.setSprite(&smileySprite);
        toolbox.newGameButton = &smileyButton;

        // Draw new game button
        (*toolbox.newGameButton->getSprite()).setPosition(toolbox.newGameButton->getPosition());
        toolbox.window.draw(*toolbox.newGameButton->getSprite());

        // Debug button
        sf::Image debugImage;
        sf::Texture debugTexture;
        sf::Sprite debugSprite;    
        debugImage.loadFromFile("images/debug.png");
        debugTexture.loadFromImage(debugImage);
        debugSprite.setTexture(debugTexture);

        Button debugButton(sf::Vector2f((toolbox.window.getSize().x/2) + 96, 512), toggleDebugMode);
        debugButton.setSprite(&debugSprite);
        toolbox.debugButton = &debugButton;

        // Draw debug button
        (*toolbox.debugButton->getSprite()).setPosition(toolbox.debugButton->getPosition());
        toolbox.window.draw(*toolbox.debugButton->getSprite());

        // Test button 1
        sf::Image test1Image;
        sf::Texture test1Texture;
        sf::Sprite test1Sprite;    
        test1Image.loadFromFile("images/test_1.png");
        test1Texture.loadFromImage(test1Image);
        test1Sprite.setTexture(test1Texture);

        Button test1Button(sf::Vector2f((toolbox.window.getSize().x/2) + 160, 512), loadTest1);
        test1Button.setSprite(&test1Sprite);
        toolbox.testButton1 = &test1Button;

        // Draw test button 1
        (*toolbox.testButton1->getSprite()).setPosition(toolbox.testButton1->getPosition());
        toolbox.window.draw(*toolbox.testButton1->getSprite());  

        // Test button 2
        sf::Image test2Image;
        sf::Texture test2Texture;
        sf::Sprite test2Sprite;    
        test2Image.loadFromFile("images/test_2.png");
        test2Texture.loadFromImage(test2Image);
        test2Sprite.setTexture(test2Texture);

        Button test2Button(sf::Vector2f((toolbox.window.getSize().x/2) + 224, 512), loadTest2);
        test2Button.setSprite(&test2Sprite);
        toolbox.testButton2 = &test2Button;
        
        // Draw test button 2
        (*toolbox.testButton2->getSprite()).setPosition(toolbox.testButton2->getPosition());
        toolbox.window.draw(*toolbox.testButton2->getSprite());     

        // Draw tiles
        for (int y = 0; y < 16; y++)
        {
            for (int x = 0; x < 25; x++)
            {   
                toolbox.gameState->getTile(y,x)->draw();
            }   
        }

        toolbox.window.display();
    }

    return 0;
}