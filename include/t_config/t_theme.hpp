#pragma once

#include "ftxui/component/component_base.hpp"
#include "ftxui/screen/color.hpp"
#include "t_renderer/t_color.hpp"

#include <vector>

namespace Tetris::Config
{
class Theme
{
  public:

    std::string name = "Default";

    std::vector<ftxui::Color> mainColors = {ftxui::Color::Default};
    std::vector<ftxui::Color> gameOverColors = {ftxui::Color::Default};

    ftxui::Color mainColor = ftxui::Color::Default;
    ftxui::Color gameOverColor = ftxui::Color::Default;

    ftxui::Color valueColor = ftxui::Color::Default;
    ftxui::Color trueColor = ftxui::Color::Default;
    ftxui::Color falseColor = ftxui::Color::Default;

    ftxui::Color IColor = ftxui::Color::Default;
    ftxui::Color OColor = ftxui::Color::Default;
    ftxui::Color TColor = ftxui::Color::Default;
    ftxui::Color JColor = ftxui::Color::Default;
    ftxui::Color LColor = ftxui::Color::Default;
    ftxui::Color SColor = ftxui::Color::Default;
    ftxui::Color ZColor = ftxui::Color::Default;

    void apply();
    void setDefault();

    ftxui::Component getDebugRenderer();
};
} // namespace Tetris::Config