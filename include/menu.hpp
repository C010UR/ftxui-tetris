#pragma once

#include <corecrt.h>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>
#include <vector>

#include "config.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/node.hpp"
#include "ftxui/screen/color.hpp"
#include "output_helper.hpp"

namespace Tetris
{
class Menu
{
  private:
    Tetris::Config &config;

    ftxui::ScreenInteractive &screen;

    ftxui::Component mainMenuRenderer;
    ftxui::Component gameOverRenderer;
    ftxui::Component optionsRenderer;
    ftxui::Component controlsRenderer;
    ftxui::Component controlsChangeModalRenderer;

    std::vector<ftxui::Component> menuInputEntries;
    ftxui::Component              menuInputs;

    std::vector<ftxui::Component> gameOverInputEntries;
    ftxui::Component              gameOverInputs;

    std::vector<ftxui::Component> optionInputEntries;
    ftxui::Component              optionInputs;

    std::vector<ftxui::Component> controlInputEntries;
    ftxui::Component              controlInputs;

    std::vector<std::string> toggleDebugModeEntries;
    std::vector<std::string> toggleEasyModeEntries;

    Tetris::Menus         currentMenu;
    int                   currentMenuIndex;
    Tetris::MenuExitCodes exitCode;

    bool                isModalOpen = false;
    Tetris::TriggerType controlChangeInputType;

  private:
    void changeMenu(Tetris::Menus menu)
    {
        this->currentMenu = menu;

        switch (menu)
        {

        case Menus::MAIN_MENU:
            this->currentMenuIndex = 0;
            break;
        case Menus::GAME_OVER:
            this->currentMenuIndex = 1;
            break;
        case Menus::OPTIONS:
            this->currentMenuIndex = 2;
            break;
        case Menus::CONTROLS:
            this->currentMenuIndex = 3;
        }
    }

    void startGame()
    {
        this->exitCode = Tetris::MenuExitCodes::START_GAME;
        this->screen.Exit();
    }

    void exitGame()
    {
        this->exitCode = Tetris::MenuExitCodes::EXIT_GAME;
        this->screen.Exit();
    }

    void initializeMainMenu()
    {
        this->menuInputEntries = {
            ftxui::Button(
                "Start Game",
                [this] { this->startGame(); },
                ftxui::ButtonOption::Animated(
                    ftxui::Color::Default, ftxui::Color::GrayDark, ftxui::Color::Default, ftxui::Color::RGB(76, 204, 63)
                )
            ),
            ftxui::Button(
                "Options",
                [this] { this->changeMenu(Tetris::Menus::OPTIONS); },
                ftxui::ButtonOption::Animated(
                    ftxui::Color::Default, ftxui::Color::GrayDark, ftxui::Color::Default, ftxui::Color::RGB(76, 199, 71)
                )
            ),
            ftxui::Button(
                "Controls",
                [this] { this->changeMenu(Tetris::Menus::CONTROLS); },
                ftxui::ButtonOption::Animated(
                    ftxui::Color::Default,
                    ftxui::Color::GrayDark,
                    ftxui::Color::Default,
                    ftxui::Color::RGB(75, 179, 101)
                )
            ),
            ftxui::Button(
                "Exit",
                [this] { this->exitGame(); },
                ftxui::ButtonOption::Animated(
                    ftxui::Color::Default,
                    ftxui::Color::GrayDark,
                    ftxui::Color::Default,
                    ftxui::Color::RGB(74, 158, 131)
                )
            )};

        this->menuInputs = ftxui::Container::Vertical(this->menuInputEntries);

        this->mainMenuRenderer = ftxui::Renderer(this->menuInputs, [this] {
            return ftxui::vbox(
                       {Tetris::OutputHelper::getGiantTetrisText() | ftxui::center,
                        ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 3),
                        ftxui::vbox({
                            this->menuInputEntries[0]->Render(),
                            this->menuInputEntries[1]->Render(),
                            this->menuInputEntries[2]->Render(),
                            this->menuInputEntries[3]->Render(),
                        }) | ftxui::center}
                   )
                   | ftxui::center;
        });
    }

    void initializeGameOver()
    {
        this->gameOverInputEntries = {
            ftxui::Button(
                "Main Menu",
                [this] { this->changeMenu(Tetris::Menus::MAIN_MENU); },
                ftxui::ButtonOption::Animated(
                    ftxui::Color::Default, ftxui::Color::GrayDark, ftxui::Color::Default, ftxui::Color::RGB(196, 55, 37)
                )
            ),
            ftxui::Button(
                "Try Again",
                [this] { this->startGame(); },
                ftxui::ButtonOption::Animated(
                    ftxui::Color::Default, ftxui::Color::GrayDark, ftxui::Color::Default, ftxui::Color::RGB(160, 45, 50)
                )
            ),
            ftxui::Button(
                "Exit",
                [this] { this->exitGame(); },
                ftxui::ButtonOption::Animated(
                    ftxui::Color::Default, ftxui::Color::GrayDark, ftxui::Color::Default, ftxui::Color::RGB(87, 25, 75)
                )
            )};

        this->gameOverInputs = ftxui::Container::Vertical(this->gameOverInputEntries);

        this->gameOverRenderer = ftxui::Renderer(this->gameOverInputs, [this] {
            return ftxui::vbox(
                       {Tetris::OutputHelper::getGiantGameOverText() | ftxui::center,
                        ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 3),
                        ftxui::vbox({
                            this->gameOverInputEntries[0]->Render(),
                            this->gameOverInputEntries[1]->Render(),
                            this->gameOverInputEntries[2]->Render(),
                        }) | ftxui::center}
                   )
                   | ftxui::center;
        });
    }

    void initializeOptions()
    {
        this->toggleDebugModeEntries = {"Off", "On"};
        this->toggleEasyModeEntries  = {"Off", "On"};

        this->optionInputEntries = {
            ftxui::Toggle(&this->toggleDebugModeEntries, &(this->config.isDebug)),
            ftxui::Toggle(&this->toggleEasyModeEntries, &(this->config.isEasyMode)),
            ftxui::Button(
                "-",
                [this] { this->config.storeDelay = std::max(0, this->config.storeDelay - 50); },
                ftxui::ButtonOption::Ascii()
            ),
            ftxui::Button(
                "+", [this] { this->config.storeDelay += 50; }, ftxui::ButtonOption::Ascii()
            ),
            ftxui::Button(
                "-",
                [this] { this->config.softDropDelay = std::max(0, this->config.softDropDelay - 10); },
                ftxui::ButtonOption::Ascii()
            ),
            ftxui::Button(
                "+", [this] { this->config.softDropDelay += 10; }, ftxui::ButtonOption::Ascii()
            ),
            ftxui::Button(
                "-",
                [this] { this->config.comboDelay = std::max(0, this->config.comboDelay - 500); },
                ftxui::ButtonOption::Ascii()
            ),
            ftxui::Button(
                "+", [this] { this->config.comboDelay += 500; }, ftxui::ButtonOption::Ascii()
            ),
            ftxui::Button(
                "-",
                [this] { this->config.updatesPerSecond = std::max(1., this->config.updatesPerSecond - 1); },
                ftxui::ButtonOption::Ascii()
            ),
            ftxui::Button(
                "+", [this] { this->config.updatesPerSecond += 1; }, ftxui::ButtonOption::Ascii()
            ),
            ftxui::Button(
                "-", [this] { this->config.level = std::max(1, this->config.level - 1); }, ftxui::ButtonOption::Ascii()
            ),
            ftxui::Button(
                "+", [this] { this->config.level = std::min(15, this->config.level + 1); }, ftxui::ButtonOption::Ascii()
            ),
            ftxui::Button(
                "Back",
                [this] { this->changeMenu(Tetris::Menus::MAIN_MENU); },
                ftxui::ButtonOption::Animated(
                    ftxui::Color::Default,
                    ftxui::Color::GrayDark,
                    ftxui::Color::Default,
                    ftxui::Color::RGB(74, 158, 131)
                )
            )};

        this->optionInputs = ftxui::Container::Vertical(
            {this->optionInputEntries[0],
             this->optionInputEntries[1],
             ftxui::Container::Horizontal({
                 this->optionInputEntries[2],
                 this->optionInputEntries[3],
             }),
             ftxui::Container::Horizontal({
                 this->optionInputEntries[4],
                 this->optionInputEntries[5],
             }),
             ftxui::Container::Horizontal({
                 this->optionInputEntries[6],
                 this->optionInputEntries[7],
             }),
             ftxui::Container::Horizontal({
                 this->optionInputEntries[8],
                 this->optionInputEntries[9],
             }),
             ftxui::Container::Horizontal({
                 this->optionInputEntries[10],
                 this->optionInputEntries[11],
             }),
             this->optionInputEntries[12]}
        );

        this->optionsRenderer = ftxui::Renderer(this->optionInputs, [this] {
            return ftxui::vbox(
                       {Tetris::OutputHelper::getGiantOptionsText() | ftxui::center,
                        ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 3),
                        ftxui::vbox({
                            ftxui::hbox(ftxui::text("Debug Mode:          "), this->optionInputEntries[0]->Render()),
                            ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 1),
                            ftxui::hbox(ftxui::text("Easy Mode:           "), this->optionInputEntries[1]->Render()),
                            ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 1),
                            ftxui::hbox({
                                ftxui::text("Store Delay, ms:     "),
                                this->optionInputEntries[2]->Render(),
                                ftxui::text(" " + std::to_string(this->config.storeDelay) + " ")
                                    | ftxui::color(OutputHelper::getValueColor()),
                                this->optionInputEntries[3]->Render(),
                            }),
                            ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 1),
                            ftxui::hbox({
                                ftxui::text("Soft drop delay, ms: "),
                                this->optionInputEntries[4]->Render(),
                                ftxui::text(" " + std::to_string(this->config.softDropDelay) + " ")
                                    | ftxui::color(OutputHelper::getValueColor()),
                                this->optionInputEntries[5]->Render(),
                            }),
                            ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 1),
                            ftxui::hbox({
                                ftxui::text("Combo Delay, ms:     "),
                                this->optionInputEntries[6]->Render(),
                                ftxui::text(" " + std::to_string(this->config.comboDelay) + " ")
                                    | ftxui::color(OutputHelper::getValueColor()),
                                this->optionInputEntries[7]->Render(),
                            }),
                            ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 1),
                            ftxui::hbox({
                                ftxui::text("Updates per Second:  "),
                                this->optionInputEntries[8]->Render(),
                                ftxui::text(" " + std::to_string((int)this->config.updatesPerSecond) + " ")
                                    | ftxui::color(OutputHelper::getValueColor()),
                                this->optionInputEntries[9]->Render(),
                            }),
                            ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 1),
                            ftxui::hbox({
                                ftxui::text("Starting Level:      "),
                                this->optionInputEntries[10]->Render(),
                                ftxui::text(" " + std::to_string(this->config.level) + " ")
                                    | ftxui::color(OutputHelper::getValueColor()),
                                this->optionInputEntries[11]->Render(),
                            }),
                            ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 1),
                        }) | ftxui::center,
                        this->optionInputEntries[12]->Render() | ftxui::center}
                   )
                   | ftxui::center;
        });
    }

    void handleKeyChange(Tetris::TriggerType trigger)
    {
        this->isModalOpen            = true;
        this->controlChangeInputType = trigger;
        this->currentMenuIndex       = 4;
    }

    void changeKey(std::string key = "")
    {
        this->isModalOpen = false;

        if (key == "")
        {
            return;
        }

        switch (this->controlChangeInputType)
        {

        case TriggerType::MOVE_LEFT:
            this->config.keyMoveLeft = key;
            break;
        case TriggerType::MOVE_RIGHT:
            this->config.keyMoveRight = key;
            break;
        case TriggerType::SOFT_DROP:
            this->config.keySoftDrop = key;
            break;
        case TriggerType::HARD_DROP:
            this->config.keyHardDrop = key;
            break;
        case TriggerType::ROTATE_LEFT:
            this->config.keyRotateLeft = key;
            break;
        case TriggerType::ROTATE_RIGHT:
            this->config.keyRotateRight = key;
            break;
        case TriggerType::SWAP_HOLD:
            this->config.keySwapHold = key;
            break;
        case TriggerType::FORFEIT:
            this->config.keyForfeit = key;
            break;
        default:
            return;
        }

        this->controlChangeInputType = TriggerType::NO_TRIGGER;
        this->changeMenu(this->currentMenu);
    }

    void handleControlsChangeModalEvent(ftxui::Event event)
    {
        if (!this->isModalOpen)
        {
            return;
        }

        if (event.is_cursor_reporting() || event.is_mouse())
        {
            return;
        }

        if (event == ftxui::Event::Escape)
        {
            this->changeKey();
            return;
        }

        this->changeKey(event.character());
    }

    void initializeControls()
    {
        this->controlInputEntries = {
            ftxui::Button(
                "Change",
                [this] { this->handleKeyChange(Tetris::TriggerType::MOVE_LEFT); },
                ftxui::ButtonOption::Ascii()
            ),
            ftxui::Button(
                "Change",
                [this] { this->handleKeyChange(Tetris::TriggerType::MOVE_RIGHT); },
                ftxui::ButtonOption::Ascii()
            ),
            ftxui::Button(
                "Change",
                [this] { this->handleKeyChange(Tetris::TriggerType::ROTATE_LEFT); },
                ftxui::ButtonOption::Ascii()
            ),
            ftxui::Button(
                "Change",
                [this] { this->handleKeyChange(Tetris::TriggerType::ROTATE_RIGHT); },
                ftxui::ButtonOption::Ascii()
            ),
            ftxui::Button(
                "Change",
                [this] { this->handleKeyChange(Tetris::TriggerType::SWAP_HOLD); },
                ftxui::ButtonOption::Ascii()
            ),
            ftxui::Button(
                "Change",
                [this] { this->handleKeyChange(Tetris::TriggerType::SOFT_DROP); },
                ftxui::ButtonOption::Ascii()
            ),
            ftxui::Button(
                "Change",
                [this] { this->handleKeyChange(Tetris::TriggerType::HARD_DROP); },
                ftxui::ButtonOption::Ascii()
            ),
            ftxui::Button(
                "Change", [this] { this->handleKeyChange(Tetris::TriggerType::FORFEIT); }, ftxui::ButtonOption::Ascii()
            ),
            ftxui::Button(
                "Back",
                [this] { this->changeMenu(Tetris::Menus::MAIN_MENU); },
                ftxui::ButtonOption::Animated(
                    ftxui::Color::Default,
                    ftxui::Color::GrayDark,
                    ftxui::Color::Default,
                    ftxui::Color::RGB(74, 158, 131)
                )
            )};

        this->controlInputs = ftxui::Container::Vertical(this->controlInputEntries);

        this->controlsRenderer = ftxui::Renderer(this->controlInputs, [this] {
            return ftxui::vbox(
                       {Tetris::OutputHelper::getGiantControlsText() | ftxui::center,
                        ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 3),
                        ftxui::vbox({
                            ftxui::hbox(
                                {ftxui::text("Move Left:    "),
                                 ftxui::text("\"" + this->config.keyMoveLeft + "\"")
                                     | ftxui::color(OutputHelper::getValueColor()),
                                 ftxui::filler() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 3),
                                 this->controlInputEntries[0]->Render()}
                            ),
                            ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 1),
                            ftxui::hbox(
                                {ftxui::text("Move Right:   "),
                                 ftxui::text("\"" + this->config.keyMoveRight + "\"")
                                     | ftxui::color(OutputHelper::getValueColor()),
                                 ftxui::filler() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 3),
                                 this->controlInputEntries[1]->Render()}
                            ),
                            ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 1),
                            ftxui::hbox(
                                {ftxui::text("Rotate Left:  "),
                                 ftxui::text("\"" + this->config.keyRotateLeft + "\"")
                                     | ftxui::color(OutputHelper::getValueColor()),
                                 ftxui::filler() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 3),
                                 this->controlInputEntries[2]->Render()}
                            ),
                            ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 1),
                            ftxui::hbox(
                                {ftxui::text("Rotate Right: "),
                                 ftxui::text("\"" + this->config.keyRotateRight + "\"")
                                     | ftxui::color(OutputHelper::getValueColor()),
                                 ftxui::filler() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 3),
                                 this->controlInputEntries[3]->Render()}
                            ),
                            ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 1),
                            ftxui::hbox(
                                {ftxui::text("Swap Hold:    "),
                                 ftxui::text("\"" + this->config.keySwapHold + "\"")
                                     | ftxui::color(OutputHelper::getValueColor()),
                                 ftxui::filler() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 3),
                                 this->controlInputEntries[4]->Render()}
                            ),
                            ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 1),
                            ftxui::hbox(
                                {ftxui::text("Soft Drop:    "),
                                 ftxui::text("\"" + this->config.keySoftDrop + "\"")
                                     | ftxui::color(OutputHelper::getValueColor()),
                                 ftxui::filler() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 3),
                                 this->controlInputEntries[5]->Render()}
                            ),
                            ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 1),
                            ftxui::hbox(
                                {ftxui::text("Hard Drop:    "),
                                 ftxui::text("\"" + this->config.keyHardDrop + "\"")
                                     | ftxui::color(OutputHelper::getValueColor()),
                                 ftxui::filler() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 3),
                                 this->controlInputEntries[6]->Render()}
                            ),
                            ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 1),
                            ftxui::hbox(
                                {ftxui::text("Forfeit:      "),
                                 ftxui::text("\"" + this->config.keyForfeit + "\"")
                                     | ftxui::color(OutputHelper::getValueColor()),
                                 ftxui::filler() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 3),
                                 this->controlInputEntries[7]->Render()}
                            ),
                            ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 1),
                        }) | ftxui::center,
                        this->controlInputEntries[8]->Render() | ftxui::center}
                   )
                   | ftxui::center;
        });

        this->controlsChangeModalRenderer = ftxui::Renderer([&] {
            return ftxui::vbox(
                       {ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 1),
                        ftxui::text("Press ESC to cancel or Any Button to change the control."),
                        ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 1)}
                   )
                   | ftxui::border | ftxui::center;
        });
    }

  public:
    Menu(ftxui::ScreenInteractive &screen, Tetris::Config &config, bool isGameOver)
        : config(config), screen(screen), exitCode(Tetris::MenuExitCodes::EXIT_GAME), isModalOpen(false),
          controlChangeInputType(Tetris::TriggerType::NO_TRIGGER)
    {
        this->currentMenu      = isGameOver ? Tetris::Menus::GAME_OVER : Tetris::Menus::MAIN_MENU;
        this->currentMenuIndex = isGameOver ? 1 : 0;

        this->initializeMainMenu();
        this->initializeGameOver();
        this->initializeOptions();
        this->initializeControls();
    }

    bool handleEvent(ftxui::Event event)
    {
        this->handleControlsChangeModalEvent(event);

        return false;
    }

    ftxui::Component getRenderer()
    {
        auto container = ftxui::Container::Tab(
            {this->mainMenuRenderer,
             this->gameOverRenderer,
             this->optionsRenderer,
             this->controlsRenderer,
             this->controlsChangeModalRenderer},
            &this->currentMenuIndex
        );

        return ftxui::Renderer(container, [&, this] {
            ftxui::Element document;

            switch (this->currentMenu)
            {
            case Menus::MAIN_MENU:
                document = this->mainMenuRenderer->Render();
                break;
            case Menus::GAME_OVER:
                document = this->gameOverRenderer->Render();
                break;
            case Menus::OPTIONS:
                document = this->optionsRenderer->Render();
                break;
            case Menus::CONTROLS:
                document = this->controlsRenderer->Render();
                break;
            }

            if (this->isModalOpen)
            {
                document = ftxui::dbox(
                    {document, this->controlsChangeModalRenderer->Render() | ftxui::clear_under | ftxui::center}
                );
            }

            return document;
        });
    }

    Tetris::MenuExitCodes getExitCode()
    {
        return this->exitCode;
    }
};
} // namespace Tetris