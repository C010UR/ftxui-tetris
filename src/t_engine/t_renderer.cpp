#include "t_engine/t_renderer.hpp"

#include "ftxui/component/component.hpp"
#include "ftxui/screen/color.hpp"
#include "t_engine/t_enums.hpp"
#include "t_menu/t_enums.hpp"
#include "t_renderer/t_current_theme.hpp"

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

ExitType Renderer::menuLoop(Tetris::Config::Config &config, Tetris::Config::Controls &controls, bool isGameOver)
{
    ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::Fullscreen();
    Renderer::configureScreen(screen);

    Tetris::Menu::MenuType currentMenu = Tetris::Menu::MenuType::MAIN_MENU;

    while (true)
    {
        Tetris::Menu::Menu menu = Tetris::Menu::Menu(screen, config, controls, isGameOver);

        menu.setMenu(currentMenu);

        ftxui::Component component
            = ftxui::CatchEvent(menu.getRenderer(), [&menu](ftxui::Event event) { return menu.handleEvent(event); })
              | ftxui::bgcolor(Tetris::Renderer::CurrentTheme::backgroundColor);

        screen.Loop(component);

        if (menu.exitType == Tetris::Engine::ExitType::RETRY)
        {
            currentMenu = menu.currentMenu;
        }
        else
        {
            return menu.exitType;
        }
    }
}

ExitType Renderer::gameLoop(Tetris::Config::Config &config, Tetris::Config::Controls &controls)
{
    Tetris::Game::Game game(config, controls);

    ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::Fullscreen();
    Renderer::configureScreen(screen);

    auto component
        = ftxui::CatchEvent(game.getRenderer(), [&game](ftxui::Event event) { return game.handleEvent(event); });

    ftxui::Loop loop(&screen, component | ftxui::bgcolor(Tetris::Renderer::CurrentTheme::backgroundColor));

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
                return game.exitType;
            }
        }

        screen.PostEvent(ftxui::Event::Special("render"));
    }

    return ExitType::ABORT;
}

int Renderer::mainLoop(Tetris::Config::Config &config, Tetris::Config::Controls &controls)
{
    ExitType exitType;
    bool     isGameOver = false;
    bool     isRetry    = false;

    while (true)
    {
        if (!isRetry)
        {
            exitType = Renderer::menuLoop(config, controls, isGameOver);

            if (exitType != ExitType::CONTINUE)
            {
                return EXIT_SUCCESS;
            }
        }

        exitType = Renderer::gameLoop(config, controls);

        if (exitType == ExitType::EXIT || exitType == ExitType::ABORT)
        {
            return EXIT_SUCCESS;
        }

        isGameOver = true;
        isRetry    = exitType == ExitType::RETRY;
    }

    return EXIT_SUCCESS;
}
} // namespace Tetris::Engine