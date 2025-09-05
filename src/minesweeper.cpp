#include <SFML/Graphics.hpp>
#include "minesweeper.h"

void toggleDebugMode()
{
    if (!debug)
    {
        for (int row = 0; row < toolbox.gameState->getDimensions().y; row++)
        {
            for (int col = 0; col < toolbox.gameState->getDimensions().x; col++)
            {
                if (toolbox.gameState->getTile(row, col)->getIsMine()) {
                    toolbox.gameState->getTile(row, col)->setState(Tile::EXPLODED);
                }
            }
        }

        debug = true;
    }
    else
    {
        for (int row = 0; row < toolbox.gameState->getDimensions().y; row++)
        {
            for (int col = 0; col < toolbox.gameState->getDimensions().x; col++)
            {
                if (toolbox.gameState->getTile(row, col)->getIsMine()) {
                    toolbox.gameState->getTile(row, col)->setState(Tile::HIDDEN);
                }
            }
        }

        debug = false;
    }

    cout << "Debug toggled: " << debug << endl;
}

bool getDebugMode()
{
    return debug;
}

void loadTest1()
{
    GameState *newGame = new GameState("boards/testboard1.brd");
    newGame->setPlayStatus(GameState::PLAYING);
    toolbox.gameState = newGame;

    cout << "Test 1 loaded" << endl;
}

void loadTest2()
{
    GameState *newGame = new GameState("boards/testboard2.brd");
    newGame->setPlayStatus(GameState::PLAYING);
    toolbox.gameState = newGame;

    cout << "Test 2 loaded" << endl;
}

void loadTest3()
{
    GameState *newGame = new GameState("boards/testboard3.brd");
    newGame->setPlayStatus(GameState::PLAYING);
    toolbox.gameState = newGame;

    cout << "Test 3 loaded" << endl;
}

void restart()
{
    if (debug) {
        debug = false;
    }

    GameState *newGame = new GameState(sf::Vector2i(25, 16), 50);
    newGame->setPlayStatus(GameState::PLAYING);
    toolbox.gameState = newGame;

    cout << "Game reset!" << endl;
}

void render()
{
    return;
}

int launch()
{
    restart();

    toolbox.window.create(sf::VideoMode(800, 600), "P4 - Minesweeper, Jaxon Kundrat");

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
                        if (toolbox.newGameButton->getSprite()->getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && !clicking)
                        {
                            // New game button clicked
                            toolbox.newGameButton->onClick();
                        }
                        if(toolbox.debugButton->getSprite()->getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && !clicking)
                        {
                            // Clicking debug button
                            toolbox.debugButton->onClick();
                        }
                        if(toolbox.testButton1->getSprite()->getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && !clicking)
                        {
                            // Clicking debug button
                            toolbox.testButton1->onClick();
                        }
                        if(toolbox.testButton2->getSprite()->getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && !clicking)
                        {
                            // Clicking debug button
                            toolbox.testButton2->onClick();
                        }
                        if(toolbox.testButton3->getSprite()->getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && !clicking)
                        {
                            // Clicking debug button
                            toolbox.testButton3->onClick();
                        }
                        if (event.mouseButton.y <= 512)
                        {
                            // Clicking a tile
                            toolbox.gameState->getTile(event.mouseButton.y / 32, event.mouseButton.x / 32)->onClickLeft();
                        }

                        clicking = true;
                    }

                    // RMB clicked
                    if (event.mouseButton.button == sf::Mouse::Right)
                    {
                        if (event.mouseButton.y <= 512)
                        {
                            // Flagging a tile
                            toolbox.gameState->getTile(event.mouseButton.y / 32, event.mouseButton.x / 32)->onClickRight();
                        }

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

        toolbox.window.clear(sf::Color::White);

        sf::Image digitsImage;
        sf::Texture digitsTexture;
        digitsImage.loadFromFile("images/digits.png");
        digitsTexture.loadFromImage(digitsImage);

        sf::Sprite digitsSprites[10];
        for (int i = 0; i < 10; i++)
        {
            sf::IntRect bounds(i*21, 0, 21, 32);
            digitsSprites[i] = sf::Sprite(digitsTexture, bounds);
        }

        string mineString = to_string(toolbox.gameState->getMineCount() - toolbox.gameState->getFlagCount());
        if (mineString.length() == 3) {
            int hundreds = int(mineString.at(0)) - 48;
            digitsSprites[hundreds].setPosition(0, 512);
            toolbox.window.draw(digitsSprites[hundreds]);

            int tens = int(mineString.at(1)) - 48;
            digitsSprites[tens].setPosition(21, 512);
            toolbox.window.draw(digitsSprites[tens]);

            int ones = int(mineString.at(2)) - 48;
            digitsSprites[ones].setPosition(42, 512);
            toolbox.window.draw(digitsSprites[ones]);
        }
        else if (mineString.length() == 2)
        {
            digitsSprites[0].setPosition(0, 512);
            toolbox.window.draw(digitsSprites[0]);

            int tens = int(mineString.at(0)) - 48;
            digitsSprites[tens].setPosition(21, 512);
            toolbox.window.draw(digitsSprites[tens]);

            int ones = int(mineString.at(1)) - 48;
            digitsSprites[ones].setPosition(42, 512);
            toolbox.window.draw(digitsSprites[ones]);
        }
        else
        {
            digitsSprites[0].setPosition(0, 512);
            toolbox.window.draw(digitsSprites[0]);

            digitsSprites[0].setPosition(21, 512);
            toolbox.window.draw(digitsSprites[0]);

            int ones = int(mineString.at(0)) - 48;
            digitsSprites[ones].setPosition(42, 512);
            toolbox.window.draw(digitsSprites[ones]);
        }

        sf::Image smileyImage;
        sf::Texture smileyTexture;
        sf::Sprite smileySprite;

        switch (toolbox.gameState->getPlayStatus())
        {
            case GameState::WIN:
                smileyImage.loadFromFile("images/face_win.png");
                break;

            case GameState::LOSS:
                smileyImage.loadFromFile("images/face_lose.png");
                debug = true;
                break;

            case GameState::PLAYING:
                smileyImage.loadFromFile("images/face_happy.png");
                break;
        }

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

        // Test button 3
        sf::Image test3Image;
        sf::Texture test3Texture;
        sf::Sprite test3Sprite;
        test3Image.loadFromFile("images/test_3.png");
        test3Texture.loadFromImage(test3Image);
        test3Sprite.setTexture(test3Texture);

        Button test3Button(sf::Vector2f((toolbox.window.getSize().x/2) + 288, 512), loadTest3);
        test3Button.setSprite(&test3Sprite);
        toolbox.testButton3 = &test3Button;

        // Draw test button 3
        (*toolbox.testButton3->getSprite()).setPosition(toolbox.testButton3->getPosition());
        toolbox.window.draw(*toolbox.testButton3->getSprite());

        // Draw tiles
        for (int row = 0; row < toolbox.gameState->getDimensions().y; row++)
        {
            for (int col = 0; col < toolbox.gameState->getDimensions().x; col++)
            {
                toolbox.gameState->getTile(row, col)->draw();
            }
        }

        toolbox.window.display();
    }

    return 0;
}

int main()
{
    return launch();
}