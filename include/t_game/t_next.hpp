#pragma once

#include "ftxui/dom/elements.hpp"
#include "t_game/t_tetromino.hpp"
#include "t_game/t_tetromino_factory.hpp"
#include "t_renderer/t_canvas.hpp"

#include <vector>
namespace Tetris::Game
{
class Next
{
  private:

    std::vector<Tetris::Game::Tetromino> bag;
    int                                  index;

    void checkBag();

  public:

    Next();

    Tetris::Game::Tetromino pop();

    ftxui::Element getElement();
};
} // namespace Tetris::Game