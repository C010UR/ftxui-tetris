#include "t_menu/t_menus/t_main_menu.hpp"

namespace Tetris::Menu {
void MainMenu::init(
    std::function<void()> startButtonHandler,
    std::function<void()> optionsButtonHandler,
    std::function<void()> controlsButtonHandler,
    std::function<void()> exitButtonHandler)
{
    this->startButton    = MenuHelper::getAnimatedButton("Start Game", startButtonHandler);
    this->optionsButton  = MenuHelper::getAnimatedButton("Options", optionsButtonHandler);
    this->controlsButton = MenuHelper::getAnimatedButton("Controls", controlsButtonHandler);
    this->exitButton     = MenuHelper::getAnimatedButton("Exit", exitButtonHandler);

    this->inputs =
        ftxui::Container::Vertical({this->startButton, this->optionsButton, this->controlsButton, this->exitButton});

    this->renderer = ftxui::Renderer(this->inputs, [this] {
        // clang-format off
        return ftxui::vbox({
            Tetris::Renderer::Header::tetris() | ftxui::center,
            ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 3),
            ftxui::vbox(
                {this->startButton->Render(),
                    this->optionsButton->Render(),
                    this->controlsButton->Render(),
                    this->exitButton->Render()})
                | ftxui::center
        }) | ftxui::center;
        // clang-format on
    });
}
} // namespace Tetris::Menu