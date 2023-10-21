#include <bits/chrono.h>
#include <chrono>
#include <fstream>
#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <string>
#include <vector>

#include "board.hpp"
#include "ftxui/component/loop.hpp"
#include "game.hpp"

double getCurrentTime()
{
    auto currentTime = std::chrono::high_resolution_clock::now();

    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime.time_since_epoch());

    return static_cast<double>(milliseconds.count());
}

bool mainLoop(ftxui::Loop &loop, ftxui::ScreenInteractive &screen, Tetris::Game &game, double updatesPerSecond)
{
    double const msPerUpdate = 1000 / updatesPerSecond;
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

            if (game.isGameOver()) {
                return true;
            }
        }

        screen.PostEvent(ftxui::Event::Special("render"));
    }

    return false;
}

int main(void)
{
    double const updatesPerSecond = 240.;

    Tetris::Game game(updatesPerSecond, true);

    auto screen = ftxui::ScreenInteractive::Fullscreen();

    auto cursor  = ftxui::Screen::Cursor();
    cursor.shape = ftxui::Screen::Cursor::Shape::Hidden;
    screen.SetCursor(cursor);

    auto component = ftxui::CatchEvent(game.getRenderer(true) | ftxui::center, [&game](ftxui::Event event) {
        return game.handleEvent(event);
    });

    // screen.Loop(component);

    ftxui::Loop loop(&screen, component);

    mainLoop(loop, screen, game, updatesPerSecond);

    return EXIT_SUCCESS;
}