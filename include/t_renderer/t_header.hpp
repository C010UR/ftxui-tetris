#pragma once

#include "ftxui/dom/elements.hpp"
#include "ftxui/dom/linear_gradient.hpp"
#include "t_color.hpp"

namespace Tetris::Renderer
{
class Header
{
  public:

    static ftxui::Element tetris();
    static ftxui::Element gameOver();
    static ftxui::Element options();
    static ftxui::Element controls();
};
} // namespace Tetris::Renderer