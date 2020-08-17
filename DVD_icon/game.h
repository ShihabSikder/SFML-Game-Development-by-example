#include "window.h"

class Game
{
public:
    Game();
    ~Game();

    void HandleInput();
    void Update();
    void Render();
    Window* GetWindow();
    sf::Time GetElapsed();
    void RestartClock();

private:
    void MovePlayer();
    Window m_window;
    sf::Texture m_man;
    sf::Sprite m_manSprite;
    sf::Vector2i m_increment;
    //sf::Vector2f increment;
    sf::Clock m_clock;
    sf::Time m_elapsed;
};

Window* Game::GetWindow(){
    return &m_window;
}

Game::Game() : m_window("Chapter 2", sf::Vector2u(800, 600))
{
    m_man.loadFromFile("timberman.png");
    m_manSprite.setTexture(m_man);
    m_manSprite.setOrigin(m_manSprite.getPosition().x / 2, m_manSprite.getPosition().y / 2);
    
    m_increment = sf::Vector2i(20, 20);
}
Game::~Game() {}

void Game::Update()
{
    m_window.Update();
    MovePlayer();
}

void Game::MovePlayer()
{
    sf::Vector2u l_windowSize = m_window.GetWindowSize();
    sf::Vector2u l_textureSize = m_man.getSize();

    if ((m_manSprite.getPosition().x > l_windowSize.x - l_textureSize.x && m_increment.x > 0) ||
        (m_manSprite.getPosition().x < 0 && m_increment.x < 0))
    {
        m_increment.x = -m_increment.x;
    }

    if ((m_manSprite.getPosition().y > l_windowSize.y - l_textureSize.y && m_increment.y > 0) ||
        (m_manSprite.getPosition().y < 0 && m_increment.y < 0))
    {
        m_increment.y = -m_increment.y;
    }

    float fElapsed = m_elapsed.asSeconds();

    m_manSprite.setPosition(
        m_manSprite.getPosition().x+m_increment.x*fElapsed,
        m_manSprite.getPosition().y+m_increment.y*fElapsed
    );

}

void Game::Render(){
    m_window.BeginDraw();
    m_window.Draw(m_manSprite);
    m_window.EndDraw();
}

void Game::RestartClock(){
    m_elapsed += m_clock.restart();
}