#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

using namespace std;

class Button
{
    sf::Vector2f position;
    std::function<void(void)> clickFunc;
    sf::Sprite* sprite;

public:
    Button(sf::Vector2f _position, std::function<void(void)> _onClick);

    sf::Vector2f getPosition();

    sf::Sprite* getSprite();

    void setSprite(sf::Sprite* _sprite);

    void onClick();
};