#pragma once

#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/dom/node.hpp"
#include "t_config/t_config.hpp"
#include "t_config/t_controls.hpp"
#include "t_engine/t_enums.hpp"
#include "t_game/t_board.hpp"
#include "t_game/t_enums.hpp"
#include "t_game/t_hold.hpp"
#include "t_game/t_next.hpp"
#include "t_game/t_score.hpp"
#include "t_game/t_tetromino.hpp"
#include "t_renderer/t_key_value.hpp"

#include <unordered_map>
#include <vector>

namespace Tetris::Game
{
class Game
{
  private:

    Tetris::Game::Board board;
    Tetris::Game::Score score;
    Tetris::Game::Hold  hold;
    Tetris::Game::Next  next;

    Tetris::Config::Controls controls;
    Tetris::Config::Config   config;

    unsigned storeDelayTicks;
    unsigned softDropDelayTicks;
    unsigned comboDelayTicks;

    bool isSoftDrop;

    std::vector<Tetris::Engine::Trigger> triggers;
    std::vector<Tetris::Engine::Trigger> inputTriggers;

    unsigned calculateTicks(double ms);
    double   calculateGravity();

    void handleGravity();
    void handleSoftDrop();
    void handleDrop();
    void handleStore();
    void handleSwapHold();
    void handleCombo();

  public:

    Game(Tetris::Config::Config &config, Tetris::Config::Controls &controls);

    void update();
    void handleInput();
    void handleTriggers();

    bool handleEvent(ftxui::Event event);

    ftxui::Element   getDebugElement();
    ftxui::Component getRenderer();

    bool isGameOver();
};
} // namespace Tetris::Game