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

    std::optional<Tetromino> current;

  public:

    bool isBlocked;

    Hold();

    Tetromino get();
    void      set(Tetromino tetromino);
    bool      has();

    void block();
    void unblock();

    ftxui::Element getElement();
};
} // namespace Tetris::Game