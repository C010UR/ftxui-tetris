#pragma once

#include "ftxui/dom/elements.hpp"
#include "t_color.hpp"
#include "t_game/t_point.hpp"

#include <iomanip>
#include <sstream>

namespace Tetris::Renderer
{
class KeyValue
{
  private:
    static std::string roundDouble(double value);

  public:

    static ftxui::Element create(std::string key, std::string value);
    static ftxui::Element create(std::string key, int value);
    static ftxui::Element create(std::string key, double value);
    static ftxui::Element create(std::string key, ftxui::Color color);
    static ftxui::Element create(std::string key, bool value);
    static ftxui::Element create(std::string key, Tetris::Game::Point value);
};
} // namespace Tetris::Renderer