#include<Game.h>

int main(){
    Game game;
    while (!game.getWindow()->IsDone())
    {
        game.handleInput();
        game.update();
        game.render();
        game.restartClock();
    }
    
}