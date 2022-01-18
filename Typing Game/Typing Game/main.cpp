#include "Game.h"

int main()
{
    Game game;
    Clock clock;
    while (game.isRunning())
    {
        //game.setDeltaTime(clock.restart().asSeconds());
        game.update();
        game.render();
    }
    return 0;
}