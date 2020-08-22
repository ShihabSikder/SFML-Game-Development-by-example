#include<SFML/Graphics.hpp>

class SnakeSegment
{
public:
    SnakeSegment(int x, int y);
    sf::Vector2i getPosition();
    void setPosition(sf::Vector2i l_position);

private:
    sf::Vector2i m_position;
};

enum class Direction{None,Up,Down,Left,Right};
using SnakeContainer = std::vector<SnakeSegment>;

class Snake{
    public:
        Snake(int l_blockSize);
        ~Snake();

        //Helper Methods

        void SetDirection(Direction l_dir);
        Direction GetDirection();
        int GetSpeed();
        sf::Vector2i GetPosition();
        int GetLives();
        int GetScore();
        void IncreaseScore();

        bool HasLost();
        
        void Lose();
        void ToggleLost();

        void Extend();
        void Reset();

        void Move();
        void Tick();
        void Cut(int l_segments); //cutting thr snake
        void Render(sf::RenderWindow& l_window);

    private:
        void CheckCollision();
        SnakeContainer m_snakeBody; //Segment Vector
        int m_size;
        Direction m_dir;
        int m_speed;
        int m_lives;
        int m_score;
        bool m_lost;

        sf::RectangleShape m_bodyRect;
};