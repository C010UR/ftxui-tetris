#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

#include "board.hpp"
#include "game.hpp"

int main(void)
{
    Tetris::Game game;

    auto screen = ftxui::ScreenInteractive::FitComponent();

    auto component
        = ftxui::CatchEvent(game.getRenderer(true), [&game](ftxui::Event event) { return game.handleEvent(event); });

    screen.Loop(component);
}