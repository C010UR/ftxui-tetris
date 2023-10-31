#pragma once

#include "ftxui/dom/linear_gradient.hpp"
#include "ftxui/screen/color.hpp"

#include <vector>

namespace Tetris::Renderer
{
class CurrentTheme
{
  public:

    static std::vector<ftxui::Color> mainColors;
    static std::vector<ftxui::Color> gameOverColors;

    static ftxui::Color mainColor;
    static ftxui::Color gameOverColor;
    
    static ftxui::Color backgroundColor;
    static ftxui::Color foregroundColor;

    static ftxui::Color valueColor;
    static ftxui::Color trueColor;
    static ftxui::Color falseColor;

    static ftxui::Color IColor;
    static ftxui::Color OColor;
    static ftxui::Color TColor;
    static ftxui::Color JColor;
    static ftxui::Color LColor;
    static ftxui::Color SColor;
    static ftxui::Color ZColor;

    static ftxui::LinearGradient mainGradient(float angle = 0);
    static ftxui::LinearGradient badGradient(float angle = 0);
};

} // namespace Tetris::Renderer