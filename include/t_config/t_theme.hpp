#pragma once

#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/dom/node.hpp"
#include "ftxui/screen/color.hpp"
#include "t_renderer/t_current_theme.hpp"
#include "t_renderer/t_key_value.hpp"

#include <string>
#include <vector>

namespace Tetris::Config
{
class Theme
{
  public:

    std::string name = "Default";

    std::vector<ftxui::Color> mainColors     = {ftxui::Color::Default};
    std::vector<ftxui::Color> gameOverColors = {ftxui::Color::Default};

    ftxui::Color mainColor     = ftxui::Color::Default;
    ftxui::Color gameOverColor = ftxui::Color::Default;
    ftxui::Color backgroundColor = ftxui::Color::Default;

    ftxui::Color valueColor = ftxui::Color::Default;
    ftxui::Color trueColor  = ftxui::Color::Default;
    ftxui::Color falseColor = ftxui::Color::Default;

    ftxui::Color IColor = ftxui::Color::Default;
    ftxui::Color OColor = ftxui::Color::Default;
    ftxui::Color TColor = ftxui::Color::Default;
    ftxui::Color JColor = ftxui::Color::Default;
    ftxui::Color LColor = ftxui::Color::Default;
    ftxui::Color SColor = ftxui::Color::Default;
    ftxui::Color ZColor = ftxui::Color::Default;

    void apply(bool withBackground);
    void setDefault();

    ftxui::Component getDebugRenderer();
};
} // namespace Tetris::Config