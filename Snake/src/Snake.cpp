#include<Snake.h>

SnakeSegment::SnakeSegment(int x,int y):m_position(x,y){}

sf::Vector2i SnakeSegment::getPosition(){
    return m_position;
}

void SnakeSegment::setPosition(sf::Vector2i l_position){
    m_position = l_position;
}

Snake::Snake(int l_bloackSize)
{
    m_size = l_bloackSize;
    m_bodyRect.setSize(sf::Vector2f(m_size - 1, m_size - 1));
    Reset();
}

Snake::~Snake() {}

void Snake::Reset()
{
    m_snakeBody.clear();

    m_snakeBody.push_back(SnakeSegment(5, 7));
    m_snakeBody.push_back(SnakeSegment(5, 6));
    m_snakeBody.push_back(SnakeSegment(5, 5));

    SetDirection(Direction::None);

    m_speed = 15;
    m_lives = 3;
    m_score = 0;
    m_lost = false;
}

void Snake::SetDirection(Direction l_dir)
{
    m_dir = l_dir;
}

Direction Snake::GetDirection()
{
    return m_dir;
}

int Snake::GetSpeed()
{
    return m_speed;
}

sf::Vector2i Snake::GetPosition()
{
    if(!m_snakeBody.empty())
        return m_snakeBody.front().getPosition();
    else
        return sf::Vector2i(5,5);
}

int Snake::GetLives()
{
    return m_lives;
}
int Snake::GetScore()
{
    return m_score;
}

void Snake::IncreaseScore()
{
    m_score += 10;
}
bool Snake::HasLost()
{
    return m_lost;
}
void Snake::Lose()
{
    m_lost = true;
}
void Snake::ToggleLost()
{
    m_lost = !m_lost;
}

void Snake::Extend()
{
    if (m_snakeBody.empty())
        return;

    SnakeSegment &tail_head = m_snakeBody[m_snakeBody.size() - 1];

    if (m_snakeBody.size() > 1)
    {
        SnakeSegment &tail_bone = m_snakeBody[m_snakeBody.size() - 2];
        if (tail_head.getPosition().x == tail_bone.getPosition().x)
        {
            if (tail_head.getPosition().y > tail_bone.getPosition().y)
                m_snakeBody.push_back(SnakeSegment(tail_head.getPosition().x, tail_head.getPosition().y + 1));
            else
                m_snakeBody.push_back(SnakeSegment(tail_head.getPosition().x, tail_head.getPosition().y - 1));
        }
        else if (tail_head.getPosition().x > tail_bone.getPosition().x)
        {
            if (tail_head.getPosition().x > tail_bone.getPosition().x)
                m_snakeBody.push_back(SnakeSegment(tail_head.getPosition().x + 1, tail_head.getPosition().y));
            else
                m_snakeBody.push_back(SnakeSegment(tail_head.getPosition().x - 1, tail_head.getPosition().y));
        }
    }
    else
    {
        if (m_dir == Direction::Up)
            m_snakeBody.push_back(SnakeSegment(tail_head.getPosition().x, tail_head.getPosition().y + 1));
        else if (m_dir == Direction::Down)
            m_snakeBody.push_back(SnakeSegment(tail_head.getPosition().x, tail_head.getPosition().y - 1));
        else if (m_dir == Direction::Left)
            m_snakeBody.push_back(SnakeSegment(tail_head.getPosition().x - 1, tail_head.getPosition().y));
        else if (m_dir == Direction::Right)
            m_snakeBody.push_back(SnakeSegment(tail_head.getPosition().x + 1, tail_head.getPosition().y));
    }
}

void Snake::Tick()
{
    if (m_snakeBody.empty())
    {
        return;
    }
    if (m_dir == Direction::None)
    {
        return;
    }
    Move();
    CheckCollision();
}

void Snake::Move()
{
    for (int i = m_snakeBody.size() - 1; i > 0; i--)
    {
        m_snakeBody[i].setPosition(m_snakeBody[i - 1].getPosition());
    }

    if (m_dir == Direction::Left)
        m_snakeBody[0].setPosition(sf::Vector2i(m_snakeBody[0].getPosition().x - 1, m_snakeBody[0].getPosition().y));
    if (m_dir == Direction::Right)
        m_snakeBody[0].setPosition(sf::Vector2i(m_snakeBody[0].getPosition().x + 1, m_snakeBody[0].getPosition().y));
    if (m_dir == Direction::Up)
        m_snakeBody[0].setPosition(sf::Vector2i(m_snakeBody[0].getPosition().x, m_snakeBody[0].getPosition().y - 1));
    if (m_dir == Direction::Down)
        m_snakeBody[0].setPosition(sf::Vector2i(m_snakeBody[0].getPosition().x, m_snakeBody[0].getPosition().y + 1));
}

void Snake::CheckCollision()
{
    if (m_snakeBody.size() < 5)
        return;

    SnakeSegment &head = m_snakeBody.front();

    for (auto itr = m_snakeBody.begin() + 1; itr != m_snakeBody.end(); itr++)
    {
        if (itr->getPosition() == head.getPosition())
        {
            int segments = m_snakeBody.end() - itr;
            Cut(segments);
            break;
        }
    }
}

void Snake::Cut(int l_segments)
{
    for (int i = 0; i < l_segments; ++i)
        m_snakeBody.pop_back();
    --m_lives;
    if (!m_lives)
    {
        Lose();
        return;
    }
}

void Snake::Render(sf::RenderWindow &l_window)
{
    if (m_snakeBody.empty())
        return;
    auto head = m_snakeBody.begin();
    m_bodyRect.setFillColor(sf::Color::Yellow);
    m_bodyRect.setPosition(head->getPosition().x * m_size, head->getPosition().y * m_size);

    l_window.draw(m_bodyRect);
    m_bodyRect.setFillColor(sf::Color::Green);
    for (auto itr = m_snakeBody.begin() + 1; itr != m_snakeBody.end(); itr++)
    {
        m_bodyRect.setPosition(itr->getPosition().x * m_size, itr->getPosition().y * m_size);
        l_window.draw(m_bodyRect);
    } 
}