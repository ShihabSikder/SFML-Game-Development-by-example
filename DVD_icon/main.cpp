#include <SFML/Graphics.hpp>
#include"game.h"

int main()
{
    Game game;
    sf::Color color[4] = {sf::Color::White, sf::Color::Green, sf::Color::Red, sf::Color::Yellow};

    while (!game.GetWindow()->IsDone())
    {
       // game.HandleInput();
        game.Update();
        game.Render();
        sf::sleep(sf::seconds(0.2));
        game.RestartClock();
    }
}