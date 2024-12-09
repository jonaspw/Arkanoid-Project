#pragma once
#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"

class cPaddle : public cMovingGameObject //klasa Paddle dziedziczy publicznie po klasie sf::Drawable
{
public:
    cPaddle() = default; //domyslny konstruktor
    cPaddle(float x, float y); //konstruktor z dwoma parametrami x i y inicjalizuje pozycjê paletki
    ~cPaddle() override;
    sf::FloatRect getBounds() const; // zwraca otoczke paletki
    sf::Vector2f getPosition() const;
    void handleInput(); //reaguje na nacisniecia klawiszy sterujacych i odpowiednio porusza paletka
    void update() override; //aktualizuje stan paletki
    void setSpeed(const float speed);//ustawienie predkosci paletki
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override; //rysuje paletke na obiekcie target przy uzyciu obiektu states ktory przechowuje stan renderowania
private:

    sf::RectangleShape m_shape; //przechowuje ksztalt paletki
    float m_speed; //predkosc poruszania sie paletki
};

#endif // PADDLE_H
