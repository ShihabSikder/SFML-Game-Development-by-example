#include<Game.h>
#include<bits/stdc++.h>
using namespace std;
Game::Game(): m_window("Snake",sf::Vector2u(800,600)),m_snake(m_world.GetBlockSize()),m_world(sf::Vector2u(800,600)){
    m_textbox.Setup(5,14,350,sf::Vector2f(225,0));
    m_textbox.Add("Random Seed with"+std::to_string(time(NULL)));
}

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
        //cout<<m_snake.GetPosition().x<<"\t"<<m_snake.GetPosition().y<<endl;
        if(m_snake.HasLost()){
            m_snake.Reset();
        }
        m_textbox.Add("Score: "+std::to_string(m_snake.GetScore()));
    }
}

void Game::render(){
    m_window.BeginDraw();
    m_world.Render(*m_window.getRenderWindow());
    m_snake.Render(*m_window.getRenderWindow());
    m_textbox.Render(*m_window.getRenderWindow());
    m_window.EndDraw();
}

void Game::restartClock(){
    m_elpsedTime += m_clock.restart().asSeconds();
}

Window *Game::getWindow(){
    return &m_window;
}
Game::~Game(){}