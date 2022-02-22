#include "Game.h"
mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());
int main()
{
    srand(time(NULL));
    Game game;
    Clock clock;
    while (game.isRunning())
    {
        game.setDeltaTime(clock.restart().asSeconds());
        game.update();
        game.render();
    }
    return 0;
}