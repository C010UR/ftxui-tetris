#pragma once

#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/color.hpp"
#include "t_menu/t_menu_helper.hpp"
#include "t_renderer/t_current_theme.hpp"
#include "t_renderer/t_header.hpp"

#include <functional>
#include <vector>

namespace Tetris::Menu {
class MainMenu
{
  public:
    ftxui::Component startButton;
    ftxui::Component optionsButton;
    ftxui::Component controlsButton;
    ftxui::Component exitButton;

    ftxui::Component renderer;
    ftxui::Component inputs;

    MainMenu() {};

    void init(
        std::function<void()> startButtonHandler,
        std::function<void()> optionsButtonHandler,
        std::function<void()> controlsButtonHandler,
        std::function<void()> exitButtonHandler);
};
} // namespace Tetris::Menu