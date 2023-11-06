#pragma once

#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "t_config/t_config.hpp"
#include "t_config/t_controls.hpp"
#include "t_engine/t_enums.hpp"
#include "t_menu/t_enums.hpp"
#include "t_menu/t_menus/t_controls.hpp"
#include "t_menu/t_menus/t_game_over.hpp"
#include "t_menu/t_menus/t_main_menu.hpp"
#include "t_menus/t_change_key.hpp"
#include "t_menus/t_controls.hpp"
#include "t_menus/t_game_over.hpp"
#include "t_menus/t_main_menu.hpp"
#include "t_menus/t_options.hpp"

#include <string>

namespace Tetris::Menu {
class Menu
{
  private:
    Tetris::Config::Config   &config;
    Tetris::Config::Controls &controls;

    ftxui::ScreenInteractive &screen;
    ftxui::Component          tab;

    MainMenu  mainMenu;
    GameOver  gameOverMenu;
    Options   optionsMenu;
    Controls  controlsMenu;
    ChangeKey changeKeyMenu;

    int currentMenuIndex;

    void startGame();
    void exitGame();
    void restartMenu();

  public:
    MenuType                 currentMenu;
    Tetris::Engine::ExitType exitType;

    Menu(
        ftxui::ScreenInteractive &screen,
        Tetris::Config::Config   &config,
        Tetris::Config::Controls &controls,
        bool                      isGameOver = false,
        int                       lastScore  = 0);

    void setMenu(MenuType menu);

    ftxui::Component getRenderer();

    bool handleEvent(ftxui::Event event);
};
} // namespace Tetris::Menu