#pragma once

#include "ftxui/component/component.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/component/loop.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/screen/color.hpp"
#include "t_config/t_config.hpp"
#include "t_config/t_controls.hpp"
#include "t_engine/t_enums.hpp"
#include "t_game/game_data.hpp"
#include "t_game/t_game.hpp"
#include "t_menu/t_enums.hpp"
#include "t_menu/t_menu.hpp"
#include "t_renderer/t_current_theme.hpp"

#include <chrono>
#include <cstdlib>

namespace Tetris::Engine {
class Renderer
{
  private:
    static double getCurrentTime();
    static void   configureScreen(ftxui::ScreenInteractive &screen);

  public:
    static ExitType menuLoop(
        Tetris::Config::Config       &config,
        Tetris::Config::Controls     &controls,
        const bool                    isGameOver,
        const Tetris::Game::GameData &gameData);

    static ExitType
    gameLoop(Tetris::Config::Config &config, Tetris::Config::Controls &controls, Tetris::Game::GameData &gameData);
    static int mainLoop(Tetris::Config::Config &config, Tetris::Config::Controls &controls);
};
} // namespace Tetris::Engine