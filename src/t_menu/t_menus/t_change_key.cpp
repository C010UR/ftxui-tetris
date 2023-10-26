#include "t_menu/t_menus/t_change_key.hpp"

namespace Tetris::Menu
{
void ChangeKey::init(Tetris::Config::Controls &controls)
{
    this->controls = &controls;
    this->renderer = ftxui::Renderer([&] {
        return ftxui::vbox(
                   {ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 1),
                    ftxui::text("Press ESC to cancel or Any Button to change the controls"),
                    ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 1)}
               )
               | ftxui::border | ftxui::center;
    });
}

bool ChangeKey::handleEvent(ftxui::Event event)
{
    if (!this->isModalOpen || event.is_cursor_reporting() || event.is_mouse())
    {
        return false;
    }

    if (event == ftxui::Event::Escape)
    {
        this->isModalOpen = false;
        return true;
    }

    this->controls->changeKey(this->trigger, event.character());
    this->isModalOpen = false;
    return true;
}
} // namespace Tetris::Menu