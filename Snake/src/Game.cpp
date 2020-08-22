#include<Game.h>

Game::Game(): m_window("Snake",sf::Vector2u(800,600)),m_snake(m_world.GetBlockSize()),m_world(sf::Vector2u(800,600)){}

void Game::handleInput(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && m_snake.GetDirection()!= Direction::Down)
        m_snake.SetDirection(Direction::Up);

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && m_snake.GetDirection()!= Direction::Up)
        m_snake.SetDirection(Direction::Down);

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && m_snake.GetDirection()!= Direction::Right)
        m_snake.SetDirection(Direction::Left);
    
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && m_snake.GetDirection()!= Direction::Left)
        m_snake.SetDirection(Direction::Right);
}

void Game::update(){
    m_window.Update();

    float timestep = 1.0f/m_snake.GetSpeed();
    if(m_elpsedTime >= timestep){
        m_snake.Tick();
        m_world.Update(m_snake);
        m_elpsedTime -=timestep;
        if(m_snake.HasLost()){
            m_snake.Reset();
        }
    }
}

void Game::render(){
    m_window.BeginDraw();
    m_world.Render(*m_window.getRenderWindow());
    m_snake.Render(*m_window.getRenderWindow());
    m_window.EndDraw();
}

void Game::restartClock(){
    m_elpsedTime += m_clock.restart().asSeconds();
}

Window *Game::getWindow(){
    return &m_window;
}

Game::~Game(){}