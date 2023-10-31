#include "t_menu/t_menus/t_game_over.hpp"

namespace Tetris::Menu
{
void GameOver::init(
    std::function<void()> mainMenuButtonHandler,
    std::function<void()> tryAgainButtonHandler,
    std::function<void()> exitButtonHandler,
    int score = 0
)
{
    this->mainMenu = ftxui::Button(
        "Main Menu",
        mainMenuButtonHandler,
        ftxui::ButtonOption::Animated(
            Tetris::Renderer::CurrentTheme::backgroundColor,
            Tetris::Renderer::CurrentTheme::foregroundColor,
            Tetris::Renderer::CurrentTheme::backgroundColor,
            Tetris::Renderer::CurrentTheme::gameOverColor
        )
    );

    this->tryAgain = ftxui::Button(
        "Try Again",
        tryAgainButtonHandler,
        ftxui::ButtonOption::Animated(
            Tetris::Renderer::CurrentTheme::backgroundColor,
            Tetris::Renderer::CurrentTheme::foregroundColor,
            Tetris::Renderer::CurrentTheme::backgroundColor,
            Tetris::Renderer::CurrentTheme::gameOverColor
        )
    );

    this->exitButton = ftxui::Button(
        "Exit",
        exitButtonHandler,
        ftxui::ButtonOption::Animated(
            Tetris::Renderer::CurrentTheme::backgroundColor,
            Tetris::Renderer::CurrentTheme::foregroundColor,
            Tetris::Renderer::CurrentTheme::backgroundColor,
            Tetris::Renderer::CurrentTheme::gameOverColor
        )
    );

    this->inputs = ftxui::Container::Vertical({this->mainMenu, this->tryAgain, this->exitButton});

    this->renderer = ftxui::Renderer(this->inputs, [this, score] {
        return ftxui::vbox(
                   {Tetris::Renderer::Header::gameOver() | ftxui::center,
                    ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 1),
                    Tetris::Renderer::Header::number(score) | ftxui::center,
                    ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 3),
                    ftxui::vbox({this->mainMenu->Render(), this->tryAgain->Render(), this->exitButton->Render()})
                        | ftxui::center}
               )
               | ftxui::center;
    });
}
} // namespace Tetris::Menu