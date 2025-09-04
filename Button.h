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
        Button(sf::Vector2f _position, std::function<void(void)> _onClick) :         
            position(_position), 
            clickFunc(_onClick) 
        {}

        sf::Vector2f getPosition()
        {
            return this->position;
        }

        sf::Sprite* getSprite()
        {
            return this->sprite;
        }
        
        void setSprite(sf::Sprite* _sprite)
        {
            this->sprite = _sprite;
        }

        void onClick()
        {
            clickFunc();
        }
};