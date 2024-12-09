#pragma once
#ifndef BRICK_H
#define BRICK_H

#include <string>
#include <SFML/Graphics.hpp>

class cBrick : public sf::Drawable //klasa Brick dziedziczy publicznie po klasie sf::Drawable
{
public:
    double xx;
    double yy;
    std::string label;
    cBrick() = default;  
    cBrick(float x, float y, float width, float height); //konstruktor przyjmuje parametry x i y jako pozycje klocka oraz width i height jako wymiary klocka
    ~cBrick();
    sf::FloatRect getBounds() const;  //zwraca obwodke prostokata   
    bool isDestroyed() const; //zwraca czy klocek jest zniszczony
    void destroy(); //niszczy klocek
    void setColor(const sf::Color& color); // zmienia kolor klocka
    sf::Color getColor() const; // zwraca kolor klocka
    void draw(sf::RenderTarget& target, sf::RenderStates states)const; //rysuje klocek na target

 private:
  
    sf::RectangleShape m_shape; //definicja ksztaltu prostokat 
    bool m_destroyed; //czy znisczony czy nie
};

#endif // BRICK_H#pragma once
