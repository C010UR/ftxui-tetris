#include "t_menu/t_menus/t_options.hpp"

#include "ftxui/dom/elements.hpp"
#include "ftxui/dom/node.hpp"

namespace Tetris::Menu
{

void Options::init(Tetris::Config::Config &config, std::function<void()> backButtonHandler)
{
    this->config = &config;

    this->debugModeToggle = ftxui::Toggle(&this->onOffEntries, &this->config->isDebug);
    this->easyModeToggle  = ftxui::Toggle(&this->onOffEntries, &this->config->isEasyMode);

    this->addStoreDelay = ftxui::Button(
        "+", [this] { this->config->storeDelay += this->storeDelayStep; }, ftxui::ButtonOption::Ascii()
    );
    this->subStoreDelay = ftxui::Button(
        "-",
        [this] { this->config->storeDelay = std::max(0, this->config->storeDelay - this->storeDelayStep); },
        ftxui::ButtonOption::Ascii()
    );

    this->addSoftDropDelay = ftxui::Button(
        "+", [this] { this->config->softDropDelay += this->softDropDelayStep; }, ftxui::ButtonOption::Ascii()
    );
    this->subSoftDropDelay = ftxui::Button(
        "-",
        [this] { this->config->softDropDelay = std::max(0, this->config->softDropDelay - this->softDropDelayStep); },
        ftxui::ButtonOption::Ascii()
    );

    this->addComboDelay = ftxui::Button(
        "+", [this] { this->config->comboDelay += this->comboDelayStep; }, ftxui::ButtonOption::Ascii()
    );
    this->subComboDelay = ftxui::Button(
        "-",
        [this] { this->config->comboDelay = std::max(0, this->config->comboDelay - this->comboDelayStep); },
        ftxui::ButtonOption::Ascii()
    );

    this->addUpdatesPerSecond = ftxui::Button(
        "+", [this] { this->config->updatesPerSecond += this->updatesPerSecondStep; }, ftxui::ButtonOption::Ascii()
    );
    this->subUpdatesPerSecond = ftxui::Button(
        "-",
        [this] {
            this->config->updatesPerSecond = std::max(1., this->config->updatesPerSecond - this->updatesPerSecondStep);
        },
        ftxui::ButtonOption::Ascii()
    );

    this->addLevel = ftxui::Button(
        "+",
        [this] { this->config->level = std::min(this->maxLevel, this->config->level + this->levelStep); },
        ftxui::ButtonOption::Ascii()
    );
    this->subLevel = ftxui::Button(
        "-",
        [this] { this->config->level = std::max(this->minLevel, this->config->level - this->levelStep); },
        ftxui::ButtonOption::Ascii()
    );

    this->backButton = ftxui::Button(
        "Back",
        backButtonHandler,
        ftxui::ButtonOption::Animated(
            ftxui::Color::Default, ftxui::Color::GrayDark, ftxui::Color::Default, Tetris::Renderer::Color::mainColor
        )
    );

    this->nextTheme = ftxui::Button(
        ">", [this] { this->config->nextTheme(); this->config->applyTheme(); }, ftxui::ButtonOption::Ascii()
    );
    this->prevTheme = ftxui::Button(
        "<", [this] { this->config->prevTheme(); this->config->applyTheme(); }, ftxui::ButtonOption::Ascii()
    );

    this->inputs = ftxui::Container::Vertical(
        {this->debugModeToggle,
         this->easyModeToggle,
         ftxui::Container::Horizontal({
             this->subLevel,
             this->addLevel,
         }),
         ftxui::Container::Horizontal({
             this->subUpdatesPerSecond,
             this->addUpdatesPerSecond,
         }),
         ftxui::Container::Horizontal({
             this->subStoreDelay,
             this->addStoreDelay,
         }),
         ftxui::Container::Horizontal({
             this->subComboDelay,
             this->addComboDelay,
         }),
         ftxui::Container::Horizontal({
             this->subSoftDropDelay,
             this->addSoftDropDelay,
         }),
         ftxui::Container::Horizontal({
             this->prevTheme,
             this->nextTheme,
         }),
         this->backButton}
    );

    this->renderer = ftxui::Renderer(this->inputs, [this] {
        ftxui::Element element
            = ftxui::vbox(
                  {Tetris::Renderer::Header::options() | ftxui::center,
                   ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 3),
                   ftxui::vbox({
                       ftxui::hbox(ftxui::text("Debug Mode:          "), this->debugModeToggle->Render()),
                       ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 1),
                       ftxui::hbox(ftxui::text("Easy Mode:           "), this->easyModeToggle->Render()),
                       ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 1),
                       ftxui::hbox({
                           ftxui::text("Starting Level:      "),
                           this->subLevel->Render()
                               | ftxui::color(
                                   this->config->level == this->minLevel ? ftxui::Color::Default
                                                                         : Tetris::Renderer::Color::falseColor
                               ),
                           ftxui::text(" " + std::to_string(this->config->level) + " ")
                               | ftxui::color(Tetris::Renderer::Color::valueColor),
                           this->addLevel->Render()
                               | ftxui::color(
                                   this->config->level == this->maxLevel ? ftxui::Color::Default
                                                                         : Tetris::Renderer::Color::trueColor
                               ),
                       }),
                       ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 1),
                       ftxui::hbox({
                           ftxui::text("Updates per Second:  "),
                           this->subUpdatesPerSecond->Render()
                               | ftxui::color(
                                   this->config->updatesPerSecond == 1 ? ftxui::Color::Default
                                                                       : Tetris::Renderer::Color::falseColor
                               ),
                           ftxui::text(" " + std::to_string((int)this->config->updatesPerSecond) + " ")
                               | ftxui::color(Tetris::Renderer::Color::valueColor),
                           this->addUpdatesPerSecond->Render() | ftxui::color(Tetris::Renderer::Color::trueColor),
                       }),
                       ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 1),
                       ftxui::hbox({
                           ftxui::text("Store Delay, ms:     "),
                           this->subStoreDelay->Render()
                               | ftxui::color(
                                   this->config->storeDelay == 0 ? ftxui::Color::Default
                                                                 : Tetris::Renderer::Color::falseColor
                               ),
                           ftxui::text(" " + std::to_string(this->config->storeDelay) + " ")
                               | ftxui::color(Tetris::Renderer::Color::valueColor),
                           this->addStoreDelay->Render() | ftxui::color(Tetris::Renderer::Color::trueColor),
                       }),
                       ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 1),
                       ftxui::hbox({
                           ftxui::text("Combo Delay, ms:     "),
                           this->subComboDelay->Render()
                               | ftxui::color(
                                   this->config->comboDelay == 0 ? ftxui::Color::Default
                                                                 : Tetris::Renderer::Color::falseColor
                               ),
                           ftxui::text(" " + std::to_string(this->config->comboDelay) + " ")
                               | ftxui::color(Tetris::Renderer::Color::valueColor),
                           this->addComboDelay->Render() | ftxui::color(Tetris::Renderer::Color::trueColor),
                       }),
                       ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 1),
                       ftxui::hbox({
                           ftxui::text("Soft drop delay, ms: "),
                           this->subSoftDropDelay->Render()
                               | ftxui::color(
                                   this->config->softDropDelay == 0 ? ftxui::Color::Default
                                                                    : Tetris::Renderer::Color::falseColor
                               ),
                           ftxui::text(" " + std::to_string(this->config->softDropDelay) + " ")
                               | ftxui::color(Tetris::Renderer::Color::valueColor),
                           this->addSoftDropDelay->Render() | ftxui::color(Tetris::Renderer::Color::trueColor),
                       }),
                       ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 1),
                       ftxui::hbox({
                           ftxui::text("Theme:               "),
                           this->prevTheme->Render() | ftxui::color(Tetris::Renderer::Color::falseColor),
                           ftxui::text(" " + this->config->themes[this->config->currentTheme].name + " ")
                               | ftxui::color(Tetris::Renderer::Color::valueColor),
                           this->nextTheme->Render() | ftxui::color(Tetris::Renderer::Color::trueColor),
                       }),
                       ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 1),
                   }) | ftxui::center,
                   this->backButton->Render() | ftxui::center}
              )
              | ftxui::center;

        if (this->config->isDebug && !this->config->themes.empty())
        {
            element = ftxui::hbox(
                          {element,
                           ftxui::filler() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 3),
                           this->config->themes[this->config->currentTheme].getDebugRenderer()->Render()}
                      )
                      | ftxui::center;
        }

        return element;
    });
}

Options &Options::operator=(const Options &other)
{
    if (this == &other)
    {
        return *this;
    }

    this->config = other.config;

    return *this;
}
} // namespace Tetris::Menu