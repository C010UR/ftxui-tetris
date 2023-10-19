#include <fstream>
#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <string>

#include "board.hpp"
#include "ftxui/component/loop.hpp"
#include "game.hpp"

int main(void)
{
    Tetris::Game game(true);

    auto screen = ftxui::ScreenInteractive::Fullscreen();

    auto component = ftxui::CatchEvent(game.getRenderer(true) | ftxui::center, [&game](ftxui::Event event) {
        return game.handleEvent(event);
    });

    // screen.Loop(component);

    ftxui::Loop loop(&screen, component);

    while (!game.isGameOver())
    {
        loop.RunOnce();

        game.tick(screen);

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return EXIT_SUCCESS;
}