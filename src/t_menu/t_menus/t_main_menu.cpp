#include "t_menu/t_menus/t_main_menu.hpp"

namespace Tetris::Menu {
void MainMenu::init(
    std::function<void()> startButtonHandler,
    std::function<void()> optionsButtonHandler,
    std::function<void()> controlsButtonHandler,
    std::function<void()> exitButtonHandler)
{
    this->start    = MenuHelper::getAnimatedButton("Start Game", startButtonHandler);
    this->options  = MenuHelper::getAnimatedButton("Options", optionsButtonHandler);
    this->controls = MenuHelper::getAnimatedButton("Controls", controlsButtonHandler);
    this->exit     = MenuHelper::getAnimatedButton("Exit", exitButtonHandler);

    this->inputs =
        ftxui::Container::Vertical({this->start, this->options, this->controls, this->exit});

    this->renderer = ftxui::Renderer(this->inputs, [this] {
        // clang-format off
        return ftxui::vbox({
            Tetris::Renderer::Header::tetris() | ftxui::center,
            ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 3),
            ftxui::vbox(
                {this->start->Render(),
                    this->options->Render(),
                    this->controls->Render(),
                    this->exit->Render()})
                | ftxui::center
        }) | ftxui::center;
        // clang-format on
    });
}
} // namespace Tetris::Menu