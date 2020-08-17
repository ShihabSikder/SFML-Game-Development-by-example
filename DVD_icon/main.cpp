#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "DVD");
    sf::Texture man;
    man.loadFromFile("timberman.png");
    sf::Sprite manSprite(man);
    sf::Vector2u size = man.getSize();
    manSprite.setOrigin(size.x / 2, size.y / 2);
    sf::Vector2f increment(0.5f, 0.5f);
    manSprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    //manSprite.setColor(sf::Color(0,255,0,255));
    sf::Color color[4] = {sf::Color::White, sf::Color::Green, sf::Color::Red, sf::Color::Yellow};

    window.setFramerateLimit(240);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if ((manSprite.getPosition().x + size.x / 2 > window.getSize().x && increment.x > 0) ||
            (manSprite.getPosition().x - size.x / 2 < 0 && increment.x < 0))
        {
            increment.x = -increment.x;
            manSprite.setColor(color[rand() % 4]);
        }
        if ((manSprite.getPosition().y + size.y / 2 > window.getSize().y && increment.y > 0) ||
            (manSprite.getPosition().y - size.y / 2 < 0 && increment.y < 0))
        {
            increment.y = -increment.y;
            manSprite.setColor(color[rand() % 4]);
        }
        manSprite.setPosition(manSprite.getPosition() + increment);

        window.clear(sf::Color(16, 16, 16, 255));
        window.draw(manSprite);
        window.display();
    }
}