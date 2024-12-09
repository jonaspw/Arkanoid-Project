#pragma once
#ifndef BALL_H
#define BALL_H

#include "GameObject.h"
#include <SFML/Graphics.hpp>

class cBall : public cMovingGameObject  //klasa Ball jest dziedziczona publicznie po klasie sf::Drawable, wiec moze byc rysowana przy uzyciu funkcji draw z biblioteki SFML
{
public:
    cBall() = default;  //konstruktor domyslny
    cBall(float x, float y);  //konstruktor z parametrami
    ~cBall() override;
    sf::FloatRect getBounds() const;    //zwraca obwodke pilki w kwadracie
    sf::Vector2f getPosition() const ;
    void update() override;      //przesuwanie pilki i analiza czy ma sie odbic od sciany jezeli tak to odwraca parametr x albo y wektora
    void bounceUp(); //odwraca parametr y wektora 
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override; //implementacja metody wirtualnej draw z klasy bazowej sf::Drawable
    void setVelocity(const sf::Vector2f& velocity);

private:
    
    sf::CircleShape m_shape; //obiekt z biblioteki sfml umozliwia narysowanie okregu
    sf::Vector2f m_velocity; //wektor z biblioteki sfml reprezentuje predkosc pilki w dwuwymiarowej przestrzeni przechowywane w float
};

#endif // BALL_H
