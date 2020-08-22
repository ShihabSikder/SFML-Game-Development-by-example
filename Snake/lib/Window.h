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

    sf::RenderWindow* getRenderWindow();
    
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