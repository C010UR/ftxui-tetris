#include <bits/chrono.h>
#include <chrono>
#include <fstream>
#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <stdlib.h>
#include <string>
#include <vector>

#include "board.hpp"
#include "config.hpp"
#include "enums.hpp"
#include "ftxui/component/loop.hpp"
#include "game.hpp"
#include "menu.hpp"
#include "output_helper.hpp"

double getCurrentTime()
{
    auto currentTime = std::chrono::high_resolution_clock::now();

    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime.time_since_epoch());

    return static_cast<double>(milliseconds.count());
}

bool menuLoop(Tetris::Config &config, bool isGameOver)
{
    ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::Fullscreen();
    Tetris::OutputHelper::configureScreen(screen);

    Tetris::Menu menu = Tetris::Menu(screen, config, isGameOver);

    auto component = ftxui::CatchEvent(menu.getRenderer() | ftxui::center, [&menu](ftxui::Event event) {
        return menu.handleEvent(event);
    });
    screen.Loop(component);

    return menu.getExitCode() == Tetris::MenuExitCodes::START_GAME;
}

bool mainLoop(Tetris::Config &config)
{
    Tetris::Game game(config);

    ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::Fullscreen();
    Tetris::OutputHelper::configureScreen(screen);

    auto component = ftxui::CatchEvent(game.getRenderer() | ftxui::center, [&game](ftxui::Event event) {
        return game.handleEvent(event);
    });

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
        game.handleTriggers();

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

    return false;
}

int main(void)
{
    Tetris::Config config;

    bool isGameOver  = false;
    bool isStartGame = false;

    while (true)
    {
        isStartGame = menuLoop(config, isGameOver);

        if (!isStartGame)
        {
            return EXIT_SUCCESS;
        }

        mainLoop(config);

        isGameOver = true;
    }

    return EXIT_SUCCESS;
}