#pragma once
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"
#include <vector>

class cGame
{
public:
    cGame(sf::RenderWindow& window); //konstruktor z referencja do okna aplikacji
    ~cGame();
    void run(); //glowna petla

private:
    void processEvents(); //obsluga zdarzen generowanych przez okno
    void update(); //aktualiuje stan obiektow w grze
    void render(); //narysowanie obiektow na ekranie

    sf::RenderWindow& m_window;
    cPaddle m_paddle; //obiekt klasy paddle
    cBall m_ball; //obiekt klasy ball
    std::vector<cBrick> m_bricks; //wektor przechwywujacy cegielki
};

#endif // GAME_H

