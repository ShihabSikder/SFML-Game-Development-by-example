#include<Game.h>

int main(){
    srand((int)time(0));
    Game game;
    while (!game.getWindow()->IsDone())
    {
        game.handleInput();
        game.update();
        game.render();
        game.restartClock();
    }
    return 0;
}