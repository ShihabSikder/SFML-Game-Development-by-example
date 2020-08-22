#include<World.h>
#include<Window.h>
#include<Textbox.h>
class Game{
    public:
        Game();
        ~Game();

        void handleInput();
        void update();
        void render();
        void restartClock();
        float m_elpsedTime;
        Window *getWindow();

    private:
        Window m_window;
        World m_world;
        Snake m_snake;
        TextBox m_textbox;
        sf::Clock m_clock;
};