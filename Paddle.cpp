#include "Paddle.h"

cPaddle::cPaddle(float x, float y)
{
    m_shape.setSize(sf::Vector2f(100, 20)); //ustawienie rozmiaru paletki na szerokosc 100 pikseli i wysokosc 20 pikseli.
    m_shape.setPosition(x - m_shape.getSize().x / 2, y);//ustawienie paletki w pozycji na podanych wspolrzednych x i y
    m_shape.setFillColor(sf::Color::Blue); //kolor paletki
    m_shape.setOutlineColor(sf::Color::Black);   //kolor obramowania paletki
    m_shape.setOutlineThickness(2);             //grubosc obramowania paletki
    m_speed = 10.0f; //predkosc poruszania sie paletki
}

cPaddle::~cPaddle()
{

}

void cPaddle::setSpeed(const float speed)
{
    m_speed = speed; // Ustawienie nowej prêdkoœci paletki
}

sf::FloatRect cPaddle::getBounds() const //zwraca otoczke paletki
{
    return m_shape.getGlobalBounds();
}

sf::Vector2f cPaddle::getPosition() const
{
    return m_shape.getPosition();
}


void cPaddle::handleInput() //metoda obs³uguje wejscie czyli reaguje na nacisniecia klawiszy sterujacych(lewy i prawy klawisz strzalki)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_shape.move(-1.0f * m_speed, 0); //zmniejszenie czu³oœci paletki
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_shape.move(1.0f * m_speed, 0); //zmniejszenie czu³oœci paletki
    }
}

void cPaddle::update()
{
    //ograniczenie paletki do okna gry
    if (m_shape.getPosition().x <= 0) //lewa strona
    {
        m_shape.setPosition(0, m_shape.getPosition().y);
    }
    else if (m_shape.getPosition().x + m_shape.getSize().x >= 800) //prawa strona
    {
        m_shape.setPosition(800 - m_shape.getSize().x, m_shape.getPosition().y);
    }
}

void cPaddle::draw(sf::RenderTarget& target, sf::RenderStates states) const //metoda rysuje paletke na obszarze target
{
    target.draw(m_shape, states);
}
