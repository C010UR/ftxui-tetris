#include "t_engine/t_renderer.hpp"

namespace Tetris::Engine
{
double Renderer::getCurrentTime()
{
    auto currentTime = std::chrono::high_resolution_clock::now();

    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime.time_since_epoch());

    return static_cast<double>(milliseconds.count());
}

void Renderer::configureScreen(ftxui::ScreenInteractive &screen)
{
    auto cursor  = ftxui::Screen::Cursor();
    cursor.shape = ftxui::Screen::Cursor::Shape::Hidden;
    screen.SetCursor(cursor);
}

bool Renderer::menuLoop(Tetris::Config::Config &config, Tetris::Config::Controls &controls, bool isGameOver)
{
    ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::Fullscreen();
    Renderer::configureScreen(screen);

    Tetris::Menu::Menu menu = Tetris::Menu::Menu(screen, config, controls, isGameOver);

    ftxui::Component component = ftxui::CatchEvent(menu.getRenderer() | ftxui::center, [&menu](ftxui::Event event) {
        return menu.handleEvent(event);
    });

    screen.Loop(component);

    return menu.isStartGame;
}

bool Renderer::gameLoop(Tetris::Config::Config &config, Tetris::Config::Controls &controls)
{
    Tetris::Game::Game game(config, controls);

    ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::Fullscreen();
    Renderer::configureScreen(screen);

    auto component
        = ftxui::CatchEvent(game.getRenderer(), [&game](ftxui::Event event) { return game.handleEvent(event); });

    ftxui::Loop loop(&screen, component);

    double const msPerUpdate = 1000 / config.updatesPerSecond;
    double       previous    = getCurrentTime();
    double       lag         = 0.0;

    while (!loop.HasQuitted())
    {
        double current = getCurrentTime();
        double elapsed = current - previous;
        previous       = current;
        lag += elapsed;

        loop.RunOnce();
        game.handleInput();

        while (lag >= msPerUpdate)
        {
            game.update();
            lag -= msPerUpdate;

            if (game.isGameOver())
            {
                return true;
            }
        }

        screen.PostEvent(ftxui::Event::Special("render"));
    }

    return true;
}

int Renderer::mainLoop(Tetris::Config::Config &config, Tetris::Config::Controls &controls)
{
    bool flag = false;

    while (true) {
        flag = Renderer::menuLoop(config, controls, flag);

        if (!flag) {
            return EXIT_SUCCESS;
        } 

        flag = Renderer::gameLoop(config, controls);
    }

    return EXIT_SUCCESS;
}
} // namespace Tetris::Engine