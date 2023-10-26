#include "t_menu/t_menus/t_main_menu.hpp"

namespace Tetris::Menu
{
    void MainMenu::init(
        std::function<void()> startButtonHandler,
        std::function<void()> optionsButtonHandler,
        std::function<void()> controlsButtonHandler,
        std::function<void()> exitButtonHandler
    )
    {
        this->startButton = ftxui::Button(
            "Start Game",
            startButtonHandler,
            ftxui::ButtonOption::Animated(
                ftxui::Color::Default, ftxui::Color::GrayDark, ftxui::Color::Default, Tetris::Renderer::CurrentTheme::mainColor
            )
        );

        this->optionsButton = ftxui::Button(
            "Options",
            optionsButtonHandler,
            ftxui::ButtonOption::Animated(
                ftxui::Color::Default, ftxui::Color::GrayDark, ftxui::Color::Default, Tetris::Renderer::CurrentTheme::mainColor
            )
        );

        this->controlsButton = ftxui::Button(
            "Controls",
            controlsButtonHandler,
            ftxui::ButtonOption::Animated(
                ftxui::Color::Default, ftxui::Color::GrayDark, ftxui::Color::Default, Tetris::Renderer::CurrentTheme::mainColor
            )
        );

        this->exitButton = ftxui::Button(
            "Exit",
            exitButtonHandler,
            ftxui::ButtonOption::Animated(
                ftxui::Color::Default, ftxui::Color::GrayDark, ftxui::Color::Default, Tetris::Renderer::CurrentTheme::mainColor
            )
        );

        this->inputs = ftxui::Container::Vertical(
            {this->startButton, this->optionsButton, this->controlsButton, this->exitButton}
        );

        this->renderer = ftxui::Renderer(this->inputs, [this] {
            return ftxui::vbox(
                       {Tetris::Renderer::Header::tetris() | ftxui::center,
                        ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 3),
                        ftxui::vbox(
                            {this->startButton->Render(),
                             this->optionsButton->Render(),
                             this->controlsButton->Render(),
                             this->exitButton->Render()}
                        ) | ftxui::center}
                   )
                   | ftxui::center;
        });
    }
} // namespace Tetris::Menu