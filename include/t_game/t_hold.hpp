#pragma once

#include "ftxui/dom/elements.hpp"
#include "t_game/t_tetromino.hpp"
#include "t_renderer/t_canvas.hpp"

#include <optional>

namespace Tetris::Game
{
class Hold
{
  private:

    std::optional<Tetris::Game::Tetromino> current;

  public:

    bool isBlocked;

    Hold();

    Tetris::Game::Tetromino get();
    void                    set(Tetris::Game::Tetromino tetromino);
    bool                    has();

    void block();
    void unblock();

    ftxui::Element getElement();
};
} // namespace Tetris::Game