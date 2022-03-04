#include "Game.h"
#include "EndScreen.h"
#include "TypeBox.h"
#include <fstream>
#include <map>

mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());

#pragma region LoginSystem

struct user
{
    string name;
    string password;
    bool operator == (const user& x)
    {
        return name == x.name && password == x.password;
    }
} cur;

vector <user> acc;

void input()
{
    ifstream fi("data.txt");
    string name, pass;
    acc.clear();
    while (fi >> name >> pass) acc.push_back({ name,pass });
    fi.close();
    //for (auto it : acc) cout << it.name << " " << it.password << '\n';
}

bool login()
{
    bool logged = false;
    RenderWindow window(VideoMode(600, 600), "Typing Corona", Style::Close | Style::Titlebar);
    window.setFramerateLimit(60);
    
    input();

    ofstream fo("data.txt");
    for (auto it : acc) fo << it.name << " " << it.password << '\n';

    int eType = 0;
    bool wrong = false;
    Vector2i mousePosWindow;
    Vector2f mousePosView;
    int scene = 1; //1: home, 2: login, 3: register, 4: login successfully, 5: register successfully

    Font f;
    f.loadFromFile("../Data/font.ttf");
    Text uiText;
    uiText.setFont(f);
    uiText.setFillColor(Color(82, 74, 78));
    

    Texture login, regist, submit, play, back;
    login.loadFromFile("../Data/login.png");
    regist.loadFromFile("../Data/register.png");
    submit.loadFromFile("../Data/submit.png");
    play.loadFromFile("../Data/play.png");
    back.loadFromFile("../Data/back.png");

    Sprite _login(login), _regist(regist), _submit(submit), _play(play), _back(back);
    _login.setPosition(180.f, 350.f);
    _regist.setPosition(175.f, 440.f);
    _submit.setPosition(175.f, 410.f);
    _play.setPosition(175.f, 410.f);
    _back.setPosition(20.f, 20.f);

    TypeBox name(Vector2f(240.f, 150.f), Color::White, "username:");
    TypeBox pass(Vector2f(240.f, 220.f), Color::White, "password:");
    TypeBox confirmPass(Vector2f(240.f, 290.f), Color::White, "confirm password:");

    while (window.isOpen())
    {
        mousePosWindow = Mouse::getPosition(window);
        mousePosView = window.mapPixelToCoords(mousePosWindow);
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) window.close();
            if (event.type == Event::KeyPressed) if (event.key.code == Keyboard::Escape) window.close();
            if (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left)
            {
                if (scene == 1)
                {
                    name.setStr("");
                    pass.setStr("");
                    confirmPass.setStr("");
                    name.setSelected(false);
                    pass.setSelected(false);
                    confirmPass.setSelected(false);
                    if (_login.getGlobalBounds().contains(mousePosView))
                        scene = 2;
                    if (_regist.getGlobalBounds().contains(mousePosView))
                        scene = 3;
                    continue;
                }

                if (scene == 2)
                {
                    if (_back.getGlobalBounds().contains(mousePosView)) scene = 1;
                    if (name.getBounds().contains(mousePosView))
                    {
                        name.setSelected(true);
                        pass.setSelected(false);
                    }
                    if (pass.getBounds().contains(mousePosView))
                    {
                        pass.setSelected(true);
                        name.setSelected(false);
                    }
                    if (_submit.getGlobalBounds().contains(mousePosView))
                    {
                        cur = { name.getText(), pass.getText() };
                        bool found = false;
                        for (auto it : acc) found |= (cur == it);
                        if (found)
                        {
                            name.setStr("");
                            pass.setStr("");
                            name.setSelected(false);
                            pass.setSelected(false);
                            scene = 4;
                        }
                        else
                        {
                            name.setSelected(false);
                            pass.setSelected(false);
                            name.setStr("");
                            pass.setStr("");
                            wrong = true;
                        }
                    }
                    continue;
                }

                if (scene == 3)
                {
                    if (_back.getGlobalBounds().contains(mousePosView)) scene = 1;
                    if (name.getBounds().contains(mousePosView))
                    {
                        confirmPass.setSelected(false);
                        name.setSelected(true);
                        pass.setSelected(false);
                    }
                    if (pass.getBounds().contains(mousePosView))
                    {
                        confirmPass.setSelected(false);
                        pass.setSelected(true);
                        name.setSelected(false);
                    }
                    if (confirmPass.getBounds().contains(mousePosView))
                    {
                        confirmPass.setSelected(true);
                        pass.setSelected(false);
                        name.setSelected(false);
                    }
                    if (_submit.getGlobalBounds().contains(mousePosView))
                    {
                        cur = { name.getText(), pass.getText() };
                        if (sz(cur.name) == 0 || sz(cur.password) == 0)
                        {
                            eType = 3;
                            continue;
                        }
                        string conf = confirmPass.getText();
                        bool found = false;
                        for (auto it : acc) found |= (cur.name == it.name);
                        if (!found)
                        {
                            if (conf == cur.password)
                            {
                                fo << cur.name << " " << cur.password << '\n';
                                acc.push_back(cur);
                                name.setStr("");
                                pass.setStr("");
                                confirmPass.setStr("");
                                name.setSelected(false);
                                pass.setSelected(false);
                                confirmPass.setSelected(false);
                                scene = 5;
                            }
                            else eType = 2;
                        }
                        else
                        {
                            name.setSelected(false);
                            pass.setSelected(false);
                            confirmPass.setSelected(false);
                            name.setStr("");
                            pass.setStr("");
                            confirmPass.setStr("");
                            eType = 1;
                        }
                        
                    }
                    continue;
                }

                if (scene == 4)
                {
                    if (_play.getGlobalBounds().contains(mousePosView))
                        return true;
                    continue;
                }

                if (scene == 5)
                {
                    if (_login.getGlobalBounds().contains(mousePosView)) scene = 2;
                    continue;
                }
            }

            if (event.type == Event::TextEntered)
            {
                if (scene == 2)
                {
                    name.updateText(event);
                    pass.updateText(event);
                }
                if (scene == 3)
                {
                    name.updateText(event);
                    pass.updateText(event);
                    confirmPass.updateText(event);
                }
            }
        }

        /*
            - Draw window for each scene
        */
        window.clear(Color(253, 239, 244));
        
        if (scene == 1)
        {
            uiText.setCharacterSize(18);
            uiText.setString("WELCOME TO TYPING CORONA!");
            uiText.setPosition(78.f, 200.f);
            window.draw(_login);
            window.draw(_regist);
            window.draw(uiText);
        }

        if (scene == 2)
        {
            uiText.setCharacterSize(11);
            uiText.setPosition(150, 370);
            if (wrong)
            {
                uiText.setString("Invalid username or password!");
                
            }
            else uiText.setString("");
            name.renderText(window);
            pass.renderText(window);
            window.draw(_submit);
            window.draw(uiText);
            window.draw(_back);
        }

        if (scene == 3)
        {
            uiText.setCharacterSize(11);
            uiText.setPosition(140, 370);
            if (eType == 1)
            {
                uiText.setString("The username has been taken!");
                
            }
            else if (eType == 2)
            {
                uiText.setString("   Password does not match!");
            }
            else if (eType == 3)
            {
                uiText.setString("   Please fill all fields!");
            }
            else uiText.setString("");
            name.renderText(window);
            pass.renderText(window);
            confirmPass.renderText(window);
            window.draw(_submit);
            window.draw(uiText);
            window.draw(_back);
        }

        if (scene == 4)
        {
            uiText.setCharacterSize(18);
            uiText.setString("WELCOME " + cur.name + "!");
            uiText.setOrigin(uiText.getLocalBounds().width / 2, uiText.getGlobalBounds().height / 2);
            uiText.setPosition(300.f,250.f); 
            window.draw(uiText);
            window.draw(_play);
            
        }

        if (scene == 5)
        {
            uiText.setCharacterSize(18);
            uiText.setString("REGISTER SUCCESSFULLY!");
            uiText.setPosition(110.f, 200.f);
            window.draw(uiText);
            window.draw(_login);
        }
        window.display();
    }
    return logged;
}

#pragma endregion

int main()
{
    srand(time(NULL));
    bool isLogged = login();
    if (!isLogged) return 0;
    Game game;
    Clock clock;
    while (game.isRunning())
    {
        game.setDeltaTime(clock.restart().asSeconds());
        game.update(game.isEnd);
        game.render();
        if (game.isEnd)
        {
            EndScreen end(game.points);
            bool playAgain = false;
            while (end.isRunning())
            {
                playAgain = end.update();
                end.render();
                if (playAgain) end.window->close();
            }
            if (!playAgain)
            {
                game.window->close();
                break;
            }
            else game.reset();
        }
    }
    
    return 0;
}