#include "t_menu/t_menus/t_game_over.hpp"

namespace Tetris::Menu
{
void GameOver::init(
    std::function<void()> mainMenuButtonHandler,
    std::function<void()> tryAgainButtonHandler,
    std::function<void()> exitButtonHandler
)
{
    this->mainMenu = ftxui::Button(
        "Main Menu",
        mainMenuButtonHandler,
        ftxui::ButtonOption::Animated(
            ftxui::Color::Default, ftxui::Color::GrayDark, ftxui::Color::Default, Tetris::Renderer::CurrentTheme::gameOverColor
        )
    );

    this->tryAgain = ftxui::Button(
        "Try Again",
        tryAgainButtonHandler,
        ftxui::ButtonOption::Animated(
            ftxui::Color::Default, ftxui::Color::GrayDark, ftxui::Color::Default, Tetris::Renderer::CurrentTheme::gameOverColor
        )
    );

    this->exitButton = ftxui::Button(
        "Exit",
        exitButtonHandler,
        ftxui::ButtonOption::Animated(
            ftxui::Color::Default, ftxui::Color::GrayDark, ftxui::Color::Default, Tetris::Renderer::CurrentTheme::gameOverColor
        )
    );

    this->inputs = ftxui::Container::Vertical({this->mainMenu, this->tryAgain, this->exitButton});

    this->renderer = ftxui::Renderer(this->inputs, [this] {
        return ftxui::vbox(
                   {Tetris::Renderer::Header::gameOver() | ftxui::center,
                    ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 3),
                    ftxui::vbox({this->mainMenu->Render(), this->tryAgain->Render(), this->exitButton->Render()})
                        | ftxui::center}
               )
               | ftxui::center;
    });
}
} // namespace Tetris::Menu