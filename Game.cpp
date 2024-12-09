#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>


std::vector<cBrick> operator+(std::vector<cBrick> vec, const cBrick& brick) //przeciazenie operatora + dodawanie do wektora kolejnych cegiel
{
    vec.push_back(brick);
    return vec;
}

std::ostream& operator<<(std::ostream& os, const cBrick& brick) //przeciazenie operatora << wyswietlanie informacji o zbitym klocku
{
    if (brick.isDestroyed())
        os << "Zbity klocek!";

    return os;
}

bool operator!(const cBrick& brick)
{
    return brick.isDestroyed();
}

cGame::cGame(sf::RenderWindow& window) //konstruktor przyjmuje referencje do okna aplikacji
    :  m_window(window), m_paddle(window.getSize().x / 2.0f, window.getSize().y - 50.0f),
    m_ball(window.getSize().x / 2.0f, window.getSize().y / 2.0f)
{
    //inicjalizacja skladowych obiektow gry
    m_paddle = cPaddle(window.getSize().x / 2.0f, window.getSize().y - 50.0f);
    m_ball = cBall(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

    //tworzenie cegiel
    const int numBricks = 30; //liczba cegiel
    const int rows = 3; //liczba wierszy
    const int cols = numBricks / rows; //liczba kolumn
    const int brickWidth = window.getSize().x / cols; //szerokosc cegly na postawie szerokosci okna i ilosci kolumn
    const int brickHeight = 30; //wysokosc cegly

    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            int x = col * brickWidth;
            int y = row * brickHeight;
            cBrick brick(x, y, brickWidth, brickHeight); //wektor przyjmuje wspolrzedne x y szerokosc i wysokosc
            m_bricks = m_bricks + brick; //dodawanie kolejnego elementu do wektora
        }
    }

    std::default_random_engine m_randomEngine;
    std::random_device rd;
    m_randomEngine.seed(rd()); // Inicjalizacja generatora liczb losowych

    if (!m_bricks.empty()) //ustawienie loswego klocka na czerwony kolor
    {
        std::uniform_int_distribution<size_t> dis(0, m_bricks.size() - 1);
        size_t randomIndex = dis(m_randomEngine);
        m_bricks[randomIndex].setColor(sf::Color::Red);
        m_bricks[randomIndex].label = "RUSH";
    }
}

cGame::~cGame()
{

}

void cGame::run()
{ 
    bool gameEnded = false;

    while (m_window.isOpen()) //dopoki okno jest otwarte wywowalywane sa metody 
    {
        processEvents(); 
        update();
        render();
                       
        if (m_bricks.size() == 0 || m_ball.getPosition().y > m_paddle.getPosition().y) //warunek zakonczenia gry 
        {
            gameEnded = true; //zmiana wartosci bool na true i zatrzymanie petli
            break;
        }
    }


    if (gameEnded)
    {
        //wyswietlenie przycisku "Zagraj jeszcze raz" i oczekiwanie na klikniecie
        sf::Font font;
        if (!font.loadFromFile("CoffeCake.ttf")) 
        {
           exit(0);
        }
                   
        sf::Text playAgainText; //tekst przycisku
        playAgainText.setFont(font);
        playAgainText.setString("Nacisnij aby zagrac jeszcze raz");
        playAgainText.setCharacterSize(24);
        playAgainText.setFillColor(sf::Color::Black);

        sf::Text victoryText; //tekst wygranej
        victoryText.setFont(font);
        victoryText.setString("Wygrana!!!");
        victoryText.setCharacterSize(36);
        victoryText.setFillColor(sf::Color::Black);
        victoryText.setPosition(m_window.getSize().x / 2.0f - victoryText.getLocalBounds().width / 2.0f, 50);
       
        sf::Text defeatText; //tekst przegranej
        defeatText.setFont(font);
        defeatText.setString("Przegrana :(");
        defeatText.setCharacterSize(36);
        defeatText.setFillColor(sf::Color::Black);
        defeatText.setPosition(m_window.getSize().x / 2.0f - defeatText.getLocalBounds().width / 2.0f, 50);

        sf::RectangleShape buttonBackground(sf::Vector2f(playAgainText.getLocalBounds().width + 20, playAgainText.getLocalBounds().height + 10)); //tlo przycisku na podstawie rozmiaru tekstu
        buttonBackground.setFillColor(sf::Color::White);
        buttonBackground.setOutlineThickness(2);
        buttonBackground.setOutlineColor(sf::Color::Black);
        buttonBackground.setPosition(m_window.getSize().x / 2.0f - buttonBackground.getSize().x / 2.0f, m_window.getSize().y / 2.0f - buttonBackground.getSize().y / 2.0f); //ustalenie pozycji tla przycisku
                   
        playAgainText.setPosition(buttonBackground.getPosition() + sf::Vector2f(10, 5)); //ustalenie pozycji tekstu na tle przycisku
                               
        //petla oczekujaca na klikniecie przycisku
        bool playAgainClicked = false;

        while (m_window.isOpen() && !playAgainClicked)
        {
            sf::Event event;
            while (m_window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    m_window.close();
                else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)//warunek klikniecia lewym przyciskiem myszy w polu tla przycisku
                {
                    sf::Vector2f mousePosition(event.mouseButton.x, event.mouseButton.y);
                    if (buttonBackground.getGlobalBounds().contains(mousePosition))
                    {
                        playAgainClicked = true;
                    }
                }
            }
            
            m_window.clear(sf::Color::White); //wyczyszczenie okna
            m_window.draw(buttonBackground); //tlo przycisku
            m_window.draw(playAgainText); //tekst przycisku
           
            if (m_bricks.size() == 0)
            {
                //wyswietlany tekst "Wygrana!!!" na ekranie
                m_window.draw(victoryText);
                
            }
            else if (m_ball.getPosition().y > m_paddle.getPosition().y)
            {
                //wyswietlany tekst "Przegrana :(" na ekranie
                m_window.draw(defeatText);
            }

            m_window.display();
        }
        
        //rozpoczecie nowej gry 
        if (playAgainClicked)
        {
            m_paddle = cPaddle(m_window.getSize().x / 2.0f, m_window.getSize().y - 50.0f);
            m_ball = cBall(m_window.getSize().x / 2.0f, m_window.getSize().y / 2.0f);
            std::system("cls");                     
            m_bricks.clear();

            const int numBricks = 30;
            const int rows = 3;
            const int cols = numBricks / rows;
            const int brickWidth = m_window.getSize().x / cols;
            const int brickHeight = 30;

            for (int row = 0; row < rows; ++row)
            {
                for (int col = 0; col < cols; ++col)
                {
                    int x = col * brickWidth;
                    int y = row * brickHeight;
                    cBrick brick(x, y, brickWidth, brickHeight);
                    m_bricks = m_bricks + brick;
                }
            }

            std::default_random_engine m_randomEngine;
            std::random_device rd;
            m_randomEngine.seed(rd()); // inicjalizacja generatora liczb losowych

            if (!m_bricks.empty()) //ustawienie losowego klocka na czerwony
            {
                std::uniform_int_distribution<size_t> dis(0, m_bricks.size() - 1);
                size_t randomIndex = dis(m_randomEngine);
                m_bricks[randomIndex].setColor(sf::Color::Red);
                m_bricks[randomIndex].label = "RUSH";
            }
            
            run();
        }
    }
    
}

void cGame::processEvents() //wykrycie zamkniecia okna i przekazuje obsluge wejscia paletki do odpowiedniej metody
{
    sf::Event event;
    while (m_window.pollEvent(event)) 
    {
        if (event.type == sf::Event::Closed)
            m_window.close();
    }

    m_paddle.handleInput();
}

void cGame::update()
{
    m_paddle.update(); //aktualizacja polozenia paletki
    m_ball.update(); //aktualizacja polozenia pilki
        
    //kolizja pilki z paletka
    if (m_ball.getBounds().intersects(m_paddle.getBounds()) && m_ball.getPosition().y + 10 >= m_paddle.getPosition().y - 20)
    {
        m_ball.bounceUp();
    }
      
    //kolizja pilki z ceglami
    for (auto& brick : m_bricks) //dla kazdego elementu wektora wykonaj kod
    {
        if (m_ball.getBounds().intersects(brick.getBounds()))
        {
            m_ball.bounceUp(); //obicie
            brick.destroy(); //zniszczenie klocka
            std::cout << brick <<"  Pozostalo "<<m_bricks.size()-1<<" klockow do zbicia." << std::endl; //wypisuje na konsoli ile zostalo klockow do zbicia
            if(bool isDestroyed = !brick) //przyklad uzycia przeciazenia operatora !
            if (brick.getColor() == sf::Color::Red) // Sprawdzenie koloru zbitej cegielki
            {
               m_ball.setVelocity(sf::Vector2f(12.0f, -12.0f));// zwiekszenie predkosci pilkki po uderzeniu w wylosowany specjalny klocek
               m_paddle.setSpeed(15.0f); //zwiekszenie predkosci paletki po uderzeniu w klocek specjalny
            }
        }
    }

    //usuwanie zniszczonych cegiel
    m_bricks.erase(std::remove_if(m_bricks.begin(), m_bricks.end(),[](const cBrick& brick) { return brick.isDestroyed(); }), m_bricks.end());
}

void cGame::render() //rysowanie obiektow na ekranie
{
    m_window.clear(sf::Color::White); //tlo
    m_window.draw(m_paddle); //paletka
    m_window.draw(m_ball); //pilka

    for (const auto& brick : m_bricks) //cegielki
    {
        m_window.draw(brick);

        if (!brick.label.empty()) {

            sf::Font font;
            if (!font.loadFromFile("CoffeCake.ttf")) {
                std::cerr << "Nie mo¿na za³adowaæ czcionki arial.ttf" << std::endl;

            }
            else {

                if (!brick.label.empty()) {
                    sf::Text text;
                    text.setFont(font);
                    text.setString(brick.label);
                    text.setCharacterSize(20);
                    text.setFillColor(sf::Color::Black);
                    sf::FloatRect textBounds = text.getGlobalBounds();
                    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
                    text.setPosition(brick.xx + 40, brick.yy + 20);

                    m_window.draw(text);

                    m_window.draw(text);
                }

            }
        }
    }

    m_window.display();
}