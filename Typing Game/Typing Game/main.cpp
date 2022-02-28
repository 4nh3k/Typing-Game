#include "Game.h"
#include "EndScreen.h"
mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());
int main()
{
    srand(time(NULL));
    Game game;
    Clock clock;
    while (game.isRunning() && !game.endGame())
    {
        game.setDeltaTime(clock.restart().asSeconds());
        game.update();
        game.render();
    }
    EndScreen end(game.points);
    game.window->close();
    while (end.isRunning())
    {
        end.update();
        end.render();
    }
    return 0;
}