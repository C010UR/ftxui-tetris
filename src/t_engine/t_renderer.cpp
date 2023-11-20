#include "t_engine/t_renderer.hpp"

namespace Tetris::Engine {
double Renderer::getCurrentTime()
{
    auto currentTime = std::chrono::high_resolution_clock::now();

    auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime.time_since_epoch());

    return static_cast<double>(nanoseconds.count()) / 1000000;
}

void Renderer::configureScreen(ftxui::ScreenInteractive &screen)
{
    auto cursor  = ftxui::Screen::Cursor();
    cursor.shape = ftxui::Screen::Cursor::Shape::Hidden;
    screen.SetCursor(cursor);
}

ExitType Renderer::menuLoop(
    Tetris::Config::Config       &config,
    Tetris::Config::Controls     &controls,
    const bool                    isGameOver,
    const Tetris::Game::GameData &gameData)
{
    ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::Fullscreen();
    Renderer::configureScreen(screen);

    Tetris::Menu::MenuType currentMenu =
        isGameOver ? Tetris::Menu::MenuType::GAME_OVER : Tetris::Menu::MenuType::MAIN_MENU;

    while (true) {
        Tetris::Menu::Menu menu = Tetris::Menu::Menu(screen, config, controls, isGameOver, gameData);

        menu.setMenu(currentMenu);

        ftxui::Component component = ftxui::CatchEvent(
                                         menu.getRenderer(),
                                         [&menu](ftxui::Event event) {
                                             return menu.handleEvent(event);
                                         })
                                     | ftxui::bgcolor(Tetris::Renderer::CurrentTheme::backgroundColor)
                                     | ftxui::color(Tetris::Renderer::CurrentTheme::foregroundColor);

        screen.Loop(component);

        if (menu.exitType == Tetris::Engine::ExitType::RETRY) {
            currentMenu = menu.currentMenu;
        } else {
            return menu.exitType;
        }
    }
}

ExitType
Renderer::gameLoop(Tetris::Config::Config &config, Tetris::Config::Controls &controls, Tetris::Game::GameData &gameData)
{
    Tetris::Game::Game game(config, controls);

    ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::Fullscreen();
    Renderer::configureScreen(screen);

    auto component = ftxui::CatchEvent(game.getRenderer(), [&game](ftxui::Event event) {
        return game.handleEvent(event);
    });

    ftxui::Loop loop(
        &screen,
        component | ftxui::bgcolor(Tetris::Renderer::CurrentTheme::backgroundColor)
            | ftxui::color(Tetris::Renderer::CurrentTheme::foregroundColor));

    double const msPerUpdate = 1000 / config.updatesPerSecond;

    double       frameTimeCap = config.fps > 0 ? 1000. / config.fps : 0.;
    unsigned int frames       = 0;
    double       start        = getCurrentTime();
    double       previous     = start;
    double       lag          = 0.0;

    while (!loop.HasQuitted()) {
        double current = getCurrentTime();
        double elapsed = current - previous;
        previous       = current;
        lag += elapsed;

        loop.RunOnce();
        game.handleInput();

        while (lag >= msPerUpdate) {
            game.update();
            lag -= msPerUpdate;

            if (game.isGameOver()) {
                gameData = game.getGameData();
                return game.exitType;
            }
        }

        screen.PostEvent(ftxui::Event::Special("render"));

        current = getCurrentTime();
        elapsed = current - previous;

        if (frameTimeCap > 0 && frameTimeCap > elapsed) {
            std::this_thread::sleep_for(std::chrono::milliseconds((int)(frameTimeCap - elapsed)));
        }

        current = getCurrentTime();
        elapsed = current - previous;

        frames++;
        game.frameTime = elapsed;
        game.fps       = frames / (current - start) * 1000;

        if (start > 1000) {
            frames = 0;
            start  = getCurrentTime();
        }
    }

    return ExitType::ABORT;
}

int Renderer::mainLoop(Tetris::Config::Config &config, Tetris::Config::Controls &controls)
{
    ExitType exitType;
    bool     isGameOver = false;
    bool     isRetry    = false;

    Tetris::Game::GameData gameData;

    while (true) {
        if (!isRetry) {
            exitType = Renderer::menuLoop(config, controls, isGameOver, gameData);

            if (exitType != ExitType::CONTINUE) {
                return EXIT_SUCCESS;
            }
        }

        exitType = Renderer::gameLoop(config, controls, gameData);

        if (exitType == ExitType::EXIT || exitType == ExitType::ABORT) {
            return EXIT_SUCCESS;
        }

        isGameOver = true;
        isRetry    = exitType == ExitType::RETRY;
    }

    return EXIT_SUCCESS;
}
} // namespace Tetris::Engine