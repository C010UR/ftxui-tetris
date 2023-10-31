#include "t_menu/t_menus/t_options.hpp"

#include "ftxui/component/component.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/color.hpp"
#include "t_menu/t_menu_helper.hpp"
#include "t_renderer/t_current_theme.hpp"

namespace Tetris::Menu
{
void Options::init(
    Tetris::Config::Config &config, std::function<void()> backButtonHandler, std::function<void()> restartHandler
)
{
    this->config = &config;

    this->debugModeToggle
        = MenuHelper::getAsciiButton("Toggle", [this] { this->config->isDebug = !this->config->isDebug; });
    this->easyModeToggle
        = MenuHelper::getAsciiButton("Toggle", [this] { this->config->isEasyMode = !this->config->isEasyMode; });
    this->backgroundModeToggle = MenuHelper::getAsciiButton("Toggle", [this, restartHandler] {
        this->config->withBackgroundColor = !this->config->withBackgroundColor;
        this->config->applyTheme();
        restartHandler();
    });

    this->addStoreDelay = ftxui::Button(
        "+", [this] { this->config->storeDelay += this->storeDelayStep; }, ftxui::ButtonOption::Ascii()
    );
    this->subStoreDelay = MenuHelper::getAsciiButton("-", [this] {
        this->config->storeDelay = std::max(0, this->config->storeDelay - this->storeDelayStep);
    });

    this->addSoftDropDelay
        = MenuHelper::getAsciiButton("+", [this] { this->config->softDropDelay += this->softDropDelayStep; });
    this->subSoftDropDelay = MenuHelper::getAsciiButton("-", [this] {
        this->config->softDropDelay = std::max(0, this->config->softDropDelay - this->softDropDelayStep);
    });

    this->addComboDelay = MenuHelper::getAsciiButton("+", [this] {
        this->config->comboDelay = std::max(0, this->config->comboDelay - this->comboDelayStep);
    });
    this->subComboDelay = MenuHelper::getAsciiButton("-", [this] {
        this->config->comboDelay = std::max(0, this->config->comboDelay - this->comboDelayStep);
    });

    this->addUpdatesPerSecond
        = MenuHelper::getAsciiButton("+", [this] { this->config->updatesPerSecond += this->updatesPerSecondStep; });
    this->subUpdatesPerSecond = MenuHelper::getAsciiButton("-", [this] {
        this->config->updatesPerSecond = std::max(1., this->config->updatesPerSecond - this->updatesPerSecondStep);
    });

    this->addSoftDropGravity
        = MenuHelper::getAsciiButton("+", [this] { this->config->softDropGravity += this->softDropGravityStep; });
    this->subSoftDropGravity = MenuHelper::getAsciiButton("-", [this] {
        this->config->softDropGravity = std::max(1., this->config->softDropGravity - this->softDropGravityStep);
    });

    this->addLevel = MenuHelper::getAsciiButton("+", [this] {
        this->config->level = std::min(this->maxLevel, this->config->level + this->levelStep);
    });
    this->subLevel = MenuHelper::getAsciiButton("-", [this] {
        this->config->level = std::max(this->minLevel, this->config->level - this->levelStep);
    });

    this->addFps = MenuHelper::getAsciiButton("+", [this] {
        this->config->level = std::min(0., this->config->fps + this->fpsStep);
    });
    this->subFps = MenuHelper::getAsciiButton("-", [this] {
        this->config->level = std::max(0., this->config->fps - this->fpsStep);
    });

    this->prevTheme = MenuHelper::getAsciiButton("<", [this, restartHandler] {
        this->config->prevTheme();
        this->config->applyTheme();
        restartHandler();
    });
    this->nextTheme = MenuHelper::getAsciiButton(">", [this, restartHandler] {
        this->config->nextTheme();
        this->config->applyTheme();
        restartHandler();
    });

    this->backButton = MenuHelper::getAnimatedButton("Back", backButtonHandler);

    this->inputs = ftxui::Container::Vertical(
        {ftxui::Container::Horizontal({
             this->prevTheme,
             this->nextTheme,
         }),
         this->backgroundModeToggle,
         this->easyModeToggle,
         ftxui::Container::Horizontal({
             this->subLevel,
             this->addLevel,
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
             this->subSoftDropGravity,
             this->addSoftDropGravity,
         }),
         ftxui::Container::Horizontal({
             this->subUpdatesPerSecond,
             this->addUpdatesPerSecond,
         }),
         ftxui::Container::Horizontal({
             this->subFps,
             this->addFps,
         }),
         this->debugModeToggle,
         this->backButton}
    );

    this->renderer = ftxui::Renderer(this->inputs, [this] {
        int width = 24;

        std::function<bool(int)>    basicIntValidator            = [](int value) -> bool { return value > 0; };
        std::function<bool(double)> basicDoubleValidator         = [](double value) -> bool { return value > 0; };
        std::function<bool(int)>    subLevelValidator            = [](int value) -> bool { return value > 1; };
        std::function<bool(int)>    addLevelValidator            = [](int value) -> bool { return value < 15; };
        std::function<bool(double)> subUpdatesPerSecondValidator = [](double value) -> bool { return value > 1; };

        ftxui::Element element
            = ftxui::vbox(
                  {Tetris::Renderer::Header::options() | ftxui::center,
                   ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 3),
                   ftxui::vbox({
                       MenuHelper::getHeaderElement("Theme"),
                       MenuHelper::getOptionElement(
                           "Theme",
                           this->config->themes[this->config->currentTheme].name,
                           this->prevTheme,
                           this->nextTheme,
                           width
                       ),
                       MenuHelper::getToggleOptionElement(
                           "Background", this->config->withBackgroundColor, this->backgroundModeToggle, width
                       ),
                       MenuHelper::getButtonMargin(),
                       MenuHelper::getHeaderElement("GamePlay"),
                       MenuHelper::getToggleOptionElement(
                           "Easy Mode", this->config->isEasyMode, this->easyModeToggle, width
                       ),
                       MenuHelper::getOptionElement(
                           "Starting Level",
                           this->config->level,
                           this->subLevel,
                           this->addLevel,
                           addLevelValidator,
                           subLevelValidator,
                           width
                       ),
                       MenuHelper::getOptionElement(
                           "Store Delay",
                           this->config->storeDelay,
                           this->subStoreDelay,
                           this->addStoreDelay,
                           basicIntValidator,
                           basicIntValidator,
                           width
                       ),
                       MenuHelper::getOptionElement(
                           "Combo Delay",
                           this->config->comboDelay,
                           this->subComboDelay,
                           this->addComboDelay,
                           basicIntValidator,
                           basicIntValidator,
                           width
                       ),
                       MenuHelper::getOptionElement(
                           "Soft Drop Delay",
                           this->config->softDropDelay,
                           this->subSoftDropDelay,
                           this->addSoftDropDelay,
                           basicIntValidator,
                           basicIntValidator,
                           width
                       ),
                       MenuHelper::getOptionElement(
                           "Soft Drop Gravity",
                           this->config->softDropGravity,
                           this->subSoftDropGravity,
                           this->addSoftDropGravity,
                           basicDoubleValidator,
                           basicDoubleValidator,
                           width
                       ),
                       MenuHelper::getButtonMargin(),
                       MenuHelper::getHeaderElement("Performance"),
                       MenuHelper::getOptionElement(
                           "Updates per Second",
                           this->config->updatesPerSecond,
                           this->subUpdatesPerSecond,
                           this->addUpdatesPerSecond,
                           subUpdatesPerSecondValidator,
                           basicDoubleValidator,
                           width
                       ),
                       MenuHelper::getOptionElement(
                           "Max FPS (0 = unlimited)",
                           this->config->fps,
                           this->subFps,
                           this->addFps,
                           basicDoubleValidator,
                           basicDoubleValidator,
                           width
                       ),
                       MenuHelper::getToggleOptionElement(
                           "Debug Mode", this->config->isDebug, this->debugModeToggle, width
                       ),
                       MenuHelper::getButtonMargin(),
                       ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 1),
                   }) | ftxui::center,
                   this->backButton->Render() | ftxui::center}
              )
              | ftxui::center;

        this->config->applyTheme();

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