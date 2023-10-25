#pragma once

#include "ftxui/component/component.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "t_config/t_config.hpp"
#include "t_config/t_controls.hpp"
#include "t_menu/t_menu.hpp"

#include <chrono>

namespace Tetris::Engine
{
class Renderer
{
  private:

    static double getCurrentTime();
    static void   configureScreen(ftxui::ScreenInteractive &screen);

  public:

    static bool menuLoop(Tetris::Config::Config &config, Tetris::Config::Controls &controls, bool isGameOver);
};
} // namespace Tetris::Engine