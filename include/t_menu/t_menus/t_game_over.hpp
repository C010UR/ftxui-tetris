#pragma once

#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/color.hpp"
#include "t_renderer/t_current_theme.hpp"
#include "t_renderer/t_header.hpp"

#include <functional>
#include <vector>

namespace Tetris::Menu
{
class GameOver
{
  public:

    ftxui::Component mainMenu;
    ftxui::Component tryAgain;
    ftxui::Component exitButton;

    ftxui::Component renderer;
    ftxui::Component inputs;

    GameOver(){};

    void init(
        std::function<void()> mainMenuButtonHandler,
        std::function<void()> tryAgainButtonHandler,
        std::function<void()> exitButtonHandler
    );
};
} // namespace Tetris::Menu