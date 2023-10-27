#pragma once

#include "ftxui/component/component.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/component/loop.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "t_config/t_config.hpp"
#include "t_config/t_controls.hpp"
#include "t_engine/t_enums.hpp"
#include "t_game/t_game.hpp"
#include "t_menu/t_menu.hpp"

#include <chrono>
#include <cstdlib>

namespace Tetris::Engine
{
class Renderer
{
  private:

    static double getCurrentTime();
    static void   configureScreen(ftxui::ScreenInteractive &screen);

  public:

    static ExitType menuLoop(Tetris::Config::Config &config, Tetris::Config::Controls &controls, bool isGameOver);
    static ExitType gameLoop(Tetris::Config::Config &config, Tetris::Config::Controls &controls);
    static int  mainLoop(Tetris::Config::Config &config, Tetris::Config::Controls &controls);
};
} // namespace Tetris::Engine