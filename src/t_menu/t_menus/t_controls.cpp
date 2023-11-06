#include "t_menu/t_menus/t_controls.hpp"

#include "t_menu/t_menu_helper.hpp"

namespace Tetris::Menu {
void Controls::init(
    Tetris::Config::Controls                    &controls,
    std::function<void(Tetris::Engine::Trigger)> changeKeyHandler,
    std::function<void()>                        backButtonHandler)
{
    this->controls = &controls;

    const std::string buttonText = "Change";

    this->moveLeft    = MenuHelper::getAsciiButton("Change", [changeKeyHandler] {
        changeKeyHandler(Tetris::Engine::Trigger::KEY_MOVE_LEFT);
    });
    this->moveRight   = MenuHelper::getAsciiButton("Change", [changeKeyHandler] {
        changeKeyHandler(Tetris::Engine::Trigger::KEY_MOVE_RIGHT);
    });
    this->rotateLeft  = MenuHelper::getAsciiButton("Change", [changeKeyHandler] {
        changeKeyHandler(Tetris::Engine::Trigger::KEY_ROTATE_LEFT);
    });
    this->rotateRight = MenuHelper::getAsciiButton("Change", [changeKeyHandler] {
        changeKeyHandler(Tetris::Engine::Trigger::KEY_ROTATE_RIGHT);
    });
    this->swapHold    = MenuHelper::getAsciiButton("Change", [changeKeyHandler] {
        changeKeyHandler(Tetris::Engine::Trigger::KEY_SWAP_HOLD);
    });
    this->softDrop    = MenuHelper::getAsciiButton("Change", [changeKeyHandler] {
        changeKeyHandler(Tetris::Engine::Trigger::KEY_SOFT_DROP);
    });
    this->hardDrop    = MenuHelper::getAsciiButton("Change", [changeKeyHandler] {
        changeKeyHandler(Tetris::Engine::Trigger::KEY_HARD_DROP);
    });
    this->forfeit     = MenuHelper::getAsciiButton("Change", [changeKeyHandler] {
        changeKeyHandler(Tetris::Engine::Trigger::KEY_FORFEIT);
    });
    this->retry       = MenuHelper::getAsciiButton("Change", [changeKeyHandler] {
        changeKeyHandler(Tetris::Engine::Trigger::KEY_RETRY);
    });

    this->backButton = MenuHelper::getAnimatedButton("Back", backButtonHandler);

    this->inputs = ftxui::Container::Vertical(
        {this->moveLeft,
         this->moveRight,
         this->rotateLeft,
         this->rotateRight,
         this->swapHold,
         this->softDrop,
         this->hardDrop,
         this->forfeit,
         this->retry,
         this->backButton});

    this->renderer = ftxui::Renderer(this->inputs, [this] {
        int width = 13;

        // clang-format off
        return ftxui::vbox({
            Tetris::Renderer::Header::controls(),
            ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 3),
            ftxui::vbox({
                MenuHelper::getHeaderElement("Movement"),
                MenuHelper::getControlsElement("Move Left", this->controls->moveLeft, this->moveLeft, width),
                MenuHelper::getControlsElement("Move Right", this->controls->moveRight, this->moveRight, width),
                MenuHelper::getControlsElement(
                    "Rotate Left",
                    this->controls->rotateLeft,
                    this->rotateLeft,
                    width),
                MenuHelper::getControlsElement(
                    "Rotate Right",
                    this->controls->rotateRight,
                    this->rotateRight,
                    width),
                MenuHelper::getControlsElement("Swap Hold", this->controls->swapHold, this->swapHold, width),
                MenuHelper::getControlsElement("Soft Drop", this->controls->softDrop, this->softDrop, width),
                MenuHelper::getControlsElement("Hard Drop", this->controls->hardDrop, this->hardDrop, width),
                MenuHelper::getButtonMargin(),
                MenuHelper::getHeaderElement("Other"),
                MenuHelper::getControlsElement("Forfeit", this->controls->forfeit, this->forfeit, width),
                MenuHelper::getControlsElement("Retry", this->controls->retry, this->retry, width),
                MenuHelper::getButtonMargin(),
            }) | ftxui::center,
            this->backButton->Render() | ftxui::center
        }) | ftxui::center;
        // clang-format on
    });
}

Controls &Controls::operator=(const Controls &other)
{
    if (this == &other) {
        return *this;
    }

    this->controls = other.controls;

    return *this;
}
} // namespace Tetris::Menu
