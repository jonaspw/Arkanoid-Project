#include "Ball.h"

cBall::cBall(float x, float y)
{
    m_shape.setRadius(10);      //inicjalizacja pilki o promieniu 10
    m_shape.setPosition(x - m_shape.getRadius(), y - m_shape.getRadius()); //ustalenie pozycji pilki na podstawie x i y pomiejszonej o promien
    m_shape.setFillColor(sf::Color::Cyan);     //kolor pilki 
    m_shape.setOutlineColor(sf::Color::Black);   //kolor obramowania pilki
    m_shape.setOutlineThickness(2);             //grubosc obramowania pilki
    m_velocity = sf::Vector2f(8.0f, -8.0f);   //wektor predkosci pilki
}

cBall::~cBall()
{

}

sf::FloatRect cBall::getBounds() const
{
    return m_shape.getGlobalBounds(); //metoda zwraca obramowanie pilki w kwadracie
}

sf::Vector2f cBall::getPosition() const
{
    return m_shape.getPosition();
}

void cBall::update()
{
    m_shape.move(m_velocity); //przesuwanie pilki o wektor predkosci(m_velocity)

    // Odbicie od scian
    if (m_shape.getPosition().x <= 0 || m_shape.getPosition().x + 2 * m_shape.getRadius() >= 800) //odbicie lewa i prawa sciana
    {
        m_velocity.x = -m_velocity.x;
    }
    if (m_shape.getPosition().y <= 0) //odbicie gora
    {
        m_velocity.y = -m_velocity.y;
    }
}

void cBall::setVelocity(const sf::Vector2f& velocity)
{
    m_velocity = velocity; // Ustawienie nowej prêdkoœci pi³ki
}

void cBall::bounceUp() //odbicie pilki
{
    m_velocity.y = -m_velocity.y;
}

void cBall::draw(sf::RenderTarget& target, sf::RenderStates states) const //rysowanie pilki w target i states przechowuje stan renderowania
{
    target.draw(m_shape, states);
}
