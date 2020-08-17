#include <SFML/Graphics.hpp>
#include <iostream>
class Window
{
public:
    Window();
    Window(const std::string &l_title, const sf::Vector2u &l_size);
    ~Window();
    void BeginDraw();
    void EndDraw();

    void Update();

    bool IsDone();
    bool IsFullScreen();
    sf::Vector2u GetWindowSize();
    void ToggleFullScreen();

    void Draw(sf::Drawable &l_drawable);

private:
    void setup(const std::string &l_title, const sf::Vector2u &l_size);
    void destroy();
    void Create();
    sf::RenderWindow m_window;
    sf::Vector2u m_windowSize;
    std::string m_windowTitle;
    bool m_isDone;
    bool m_isFullscreen;
};

Window::Window()
{
    setup("Window", sf::Vector2u(640, 480));
}
Window::Window(const std::string &l_title, const sf::Vector2u &l_size)
{
    setup(l_title, l_size);
}
Window::~Window() { destroy(); }

void Window::setup(const std::string &l_title, const sf::Vector2u &l_size)
{
    m_windowTitle = l_title;
    m_windowSize = l_size;
    m_isFullscreen = false;
    m_isDone = false;
    //m_window.setFramerateLimit(60);
    Create();
}

void Window::Create()
{
    auto style = (m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
    m_window.create({m_windowSize.x, m_windowSize.y, 32}, m_windowTitle, style);
}
void Window::destroy()
{
    m_window.close();
}

void Window::Update()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_window.close();
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5)
            ToggleFullScreen();
    }
}

void Window::ToggleFullScreen(){
    m_isFullscreen = !m_isFullscreen;
    destroy();
    Create();
}

void Window::BeginDraw(){
    m_window.clear(sf::Color::Black);
}
void Window::EndDraw(){
    m_window.display();
}

bool Window::IsFullScreen(){
    return m_isFullscreen;
}

bool Window::IsDone(){
    return m_isDone;
}
sf::Vector2u Window::GetWindowSize(){
    return m_windowSize;
}
void Window::Draw(sf::Drawable& l_drawable){
    m_window.draw(l_drawable);
}