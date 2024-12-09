#pragma once
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SFML/Graphics.hpp>

class cMovingGameObject : public sf::Drawable
{
public:
    virtual ~cMovingGameObject() = default;
    virtual void update() = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};

#endif // GAME_OBJECT_H
