#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Arkanoid Game"); //tworzenie okna o wymiarach 800x600 pikseli
    window.setFramerateLimit(80);
    cGame game(window); //stworzenie obiektu game przekazuje do konstruktora referencje do obiektu window
    game.run(); //wywolanie metody ktora uruchamia petle gry

    return 0;
}
