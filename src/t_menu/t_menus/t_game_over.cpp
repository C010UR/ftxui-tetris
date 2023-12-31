#include "t_menu/t_menus/t_game_over.hpp"

namespace Tetris::Menu {
void GameOver::init(
    std::function<void()>         mainMenuButtonHandler,
    std::function<void()>         tryAgainButtonHandler,
    std::function<void()>         exitButtonHandler,
    const Tetris::Game::GameData &gameData)
{
    this->mainMenu = MenuHelper::getAnimatedButton("Main Menu", mainMenuButtonHandler, true);
    this->tryAgain = MenuHelper::getAnimatedButton("Try Again", tryAgainButtonHandler, true);
    this->exit     = MenuHelper::getAnimatedButton("Exit", exitButtonHandler, true);

    this->inputs = ftxui::Container::Vertical({this->mainMenu, this->tryAgain, this->exit});

    this->renderer = ftxui::Renderer(this->inputs, [this, gameData] {
        // clang-format off
        return ftxui::vbox({
            Tetris::Renderer::Header::transform("Game Over", true) | ftxui::center,
            ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 1),
            Tetris::Renderer::Header::transform("lines: " + std::to_string(gameData.lines), true) | ftxui::center,
            ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 1),
            Tetris::Renderer::Header::transform("score: " + std::to_string(gameData.score), true) | ftxui::center,
            ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 3),
            ftxui::vbox({this->mainMenu->Render(), this->tryAgain->Render(), this->exit->Render()})
                | ftxui::center
        }) | ftxui::center;
        // clang-format on
    });
}
} // namespace Tetris::Menu