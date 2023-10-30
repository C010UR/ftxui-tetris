#include "t_menu/t_menus/t_controls.hpp"

namespace Tetris::Menu
{
ftxui::Element Controls::getRow(const std::string label, const std::string current, ftxui::Component &button)
{
    return ftxui::hbox(
        {ftxui::text(label),
         ftxui::text("\"" + Tetris::Renderer::DataTransformer::transformKey(current) + "\"")
             | ftxui::color(Tetris::Renderer::CurrentTheme::valueColor),
         ftxui::filler() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 3),
         button->Render() | ftxui::color(Tetris::Renderer::CurrentTheme::mainColor)}
    );
}

void Controls::init(
    Tetris::Config::Controls                    &controls,
    std::function<void(Tetris::Engine::Trigger)> changeKeyHandler,
    std::function<void()>                        backButtonHandler
)
{
    this->controls = &controls;

    const std::string buttonText = "Change";

    this->moveLeft = ftxui::Button(
        "Change",
        [changeKeyHandler] { changeKeyHandler(Tetris::Engine::Trigger::KEY_MOVE_LEFT); },
        ftxui::ButtonOption::Ascii()
    );
    this->moveRight = ftxui::Button(
        "Change",
        [changeKeyHandler] { changeKeyHandler(Tetris::Engine::Trigger::KEY_MOVE_RIGHT); },
        ftxui::ButtonOption::Ascii()
    );
    this->rotateLeft = ftxui::Button(
        "Change",
        [changeKeyHandler] { changeKeyHandler(Tetris::Engine::Trigger::KEY_ROTATE_LEFT); },
        ftxui::ButtonOption::Ascii()
    );
    this->rotateRight = ftxui::Button(
        "Change",
        [changeKeyHandler] { changeKeyHandler(Tetris::Engine::Trigger::KEY_ROTATE_RIGHT); },
        ftxui::ButtonOption::Ascii()
    );
    this->swapHold = ftxui::Button(
        "Change",
        [changeKeyHandler] { changeKeyHandler(Tetris::Engine::Trigger::KEY_SWAP_HOLD); },
        ftxui::ButtonOption::Ascii()
    );
    this->softDrop = ftxui::Button(
        "Change",
        [changeKeyHandler] { changeKeyHandler(Tetris::Engine::Trigger::KEY_SOFT_DROP); },
        ftxui::ButtonOption::Ascii()
    );
    this->hardDrop = ftxui::Button(
        "Change",
        [changeKeyHandler] { changeKeyHandler(Tetris::Engine::Trigger::KEY_HARD_DROP); },
        ftxui::ButtonOption::Ascii()
    );
    this->forfeit = ftxui::Button(
        "Change",
        [changeKeyHandler] { changeKeyHandler(Tetris::Engine::Trigger::KEY_FORFEIT); },
        ftxui::ButtonOption::Ascii()
    );
    this->retry = ftxui::Button(
        "Change",
        [changeKeyHandler] { changeKeyHandler(Tetris::Engine::Trigger::KEY_RETRY); },
        ftxui::ButtonOption::Ascii()
    );

    this->backButton = ftxui::Button(
        "Back",
        backButtonHandler,
        ftxui::ButtonOption::Animated(
            Tetris::Renderer::CurrentTheme::backgroundColor,
            ftxui::Color::GrayDark,
            Tetris::Renderer::CurrentTheme::backgroundColor,
            Tetris::Renderer::CurrentTheme::mainColor
        )
    );

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
         this->backButton}
    );

    this->renderer = ftxui::Renderer(this->inputs, [this] {
        return ftxui::vbox(
                   {Tetris::Renderer::Header::controls(),
                    ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 3),
                    ftxui::vbox({
                        this->getRow("Move Left:    ", this->controls->moveLeft, this->moveLeft),
                        ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 1),
                        this->getRow("Move Right:   ", this->controls->moveRight, this->moveRight),
                        ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 1),
                        this->getRow("Rotate Left:  ", this->controls->rotateLeft, this->rotateLeft),
                        ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 1),
                        this->getRow("Rotate Right: ", this->controls->rotateRight, this->rotateRight),
                        ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 1),
                        this->getRow("Swap Hold:    ", this->controls->swapHold, this->swapHold),
                        ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 1),
                        this->getRow("Soft Drop:    ", this->controls->softDrop, this->softDrop),
                        ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 1),
                        this->getRow("Hard Drop:    ", this->controls->hardDrop, this->hardDrop),
                        ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 1),
                        this->getRow("Forfeit:      ", this->controls->forfeit, this->forfeit),
                        ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 1),
                        this->getRow("Retry:        ", this->controls->retry, this->retry),
                        ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 1),
                    }) | ftxui::center,
                    this->backButton->Render() | ftxui::center}
               )
               | ftxui::center;
    });
}
Controls &Controls::operator=(const Controls &other)
{
    if (this == &other)
    {
        return *this;
    }

    this->controls = other.controls;

    return *this;
}
} // namespace Tetris::Menu
