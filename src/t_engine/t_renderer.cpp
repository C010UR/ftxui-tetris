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

    Tetris::Engine::Renderer::configureScreen(screen);

    Tetris::Menu::Menu menu = Tetris::Menu::Menu(screen, config, controls, isGameOver);

    ftxui::Component component = ftxui::CatchEvent(menu.getRenderer() | ftxui::center, [&menu](ftxui::Event event) {
        return menu.handleEvent(event);
    });

    screen.Loop(component);

    return menu.isStartGame;
}
} // namespace Tetris::Engine