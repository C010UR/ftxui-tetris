#pragma once

#include "ftxui/dom/elements.hpp"
#include "t_color.hpp"

#include <iomanip>
#include <sstream>

namespace Tetris::Renderer
{
class KeyValue
{
  public:

    static ftxui::Element create(std::string key, std::string value);
    static ftxui::Element create(std::string key, int value);
    static ftxui::Element create(std::string key, double value);
    static ftxui::Element create(std::string key, ftxui::Color color);
    static ftxui::Element create(std::string key, bool value);
};
} // namespace Tetris::Renderer