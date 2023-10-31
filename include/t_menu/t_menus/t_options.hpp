#pragma once

#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/color.hpp"
#include "t_config/t_config.hpp"
#include "t_menu/t_menu_helper.hpp"
#include "t_renderer/t_current_theme.hpp"
#include "t_renderer/t_header.hpp"

#include <functional>
#include <vector>

namespace Tetris::Menu
{
class Options
{
  private:

    Tetris::Config::Config *config;

  public:

    const std::vector<std::string> onOffEntries = {"Off", "On"};

    const int    storeDelayStep       = 50;
    const int    softDropDelayStep    = 10;
    const int    comboDelayStep       = 500;
    const double updatesPerSecondStep = 1;
    const double fpsStep              = 1;
    const int    levelStep            = 1;
    const int    softDropGravityStep  = 10;
    const int    minLevel             = 1;
    const int    maxLevel             = 15;

    ftxui::Component debugModeToggle;
    ftxui::Component easyModeToggle;
    ftxui::Component backgroundModeToggle;
    ftxui::Component addStoreDelay;
    ftxui::Component subStoreDelay;
    ftxui::Component addSoftDropDelay;
    ftxui::Component subSoftDropDelay;
    ftxui::Component addComboDelay;
    ftxui::Component subComboDelay;
    ftxui::Component addUpdatesPerSecond;
    ftxui::Component subUpdatesPerSecond;
    ftxui::Component addSoftDropGravity;
    ftxui::Component subSoftDropGravity;
    ftxui::Component addLevel;
    ftxui::Component subLevel;
    ftxui::Component prevTheme;
    ftxui::Component nextTheme;
    ftxui::Component addFps;
    ftxui::Component subFps;
    ftxui::Component backButton;

    ftxui::Component renderer;
    ftxui::Component inputs;

    Options() : config(nullptr){};

    void init(
        Tetris::Config::Config &config, std::function<void()> backButtonHandler, std::function<void()> restartHandler
    );

    Options &operator=(const Options &other);
};
} // namespace Tetris::Menu