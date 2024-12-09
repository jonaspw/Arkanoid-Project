#include "Brick.h"
#include <SFML/Graphics.hpp>
#include <string>

cBrick::cBrick(float x, float y, float width, float height)
{
    m_shape.setSize(sf::Vector2f(width, height)); //ustawia rozmiar ksztaltu na podane wartosci width i height
    m_shape.setPosition(x, y+5); //ustawia pozycje na wartosci x y wspolrzedne
    m_shape.setFillColor(sf::Color::Yellow); //kolor wypelnienia
    m_shape.setOutlineColor(sf:: Color:: Black); //kolor obramowania
    m_shape.setOutlineThickness(2); //grubosc obramowania
    m_destroyed = false; //czy klocek jest zniszczony 
    xx = x;
    yy = y;
} 

cBrick::~cBrick()
{
    
}

sf::FloatRect cBrick::getBounds() const 
{
    return m_shape.getGlobalBounds(); //zwraca obwiednie czyli obramowanie klocka
}

bool cBrick::isDestroyed() const
{
    return m_destroyed; //metoda zwraca inforamacje o stanie klocka czy zburzony czy nie
}

void cBrick::setColor(const sf::Color& color) // Dodana implementacja metody setColor
{
    m_shape.setFillColor(color);
}

sf::Color cBrick::getColor() const // Dodana implementacja metody getColor
{
    return m_shape.getFillColor();
}

void cBrick::destroy()
{
    m_destroyed = true; //metoda zmienia wartosc z false na true i burzy klocek
}

void cBrick::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_shape, states); //rysowanie klocka na targecie  
}
