#pragma once

#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/dom/node.hpp"
#include "ftxui/screen/color.hpp"
#include "t_config/t_controls.hpp"
#include "t_engine/t_enums.hpp"
#include "t_menu/t_menus/t_change_key.hpp"
#include "t_renderer/t_current_theme.hpp"
#include "t_renderer/t_data_transformer.hpp"
#include "t_renderer/t_header.hpp"

#include <algorithm>
#include <functional>
#include <vector>

namespace Tetris::Menu
{
class Controls
{
  private:

    Tetris::Config::Controls *controls;

    ftxui::Element getRow(const std::string label, const std::string current, ftxui::Component &button);

  public:

    ftxui::Component moveLeft;
    ftxui::Component moveRight;
    ftxui::Component rotateLeft;
    ftxui::Component rotateRight;
    ftxui::Component swapHold;
    ftxui::Component softDrop;
    ftxui::Component hardDrop;
    ftxui::Component forfeit;
    ftxui::Component backButton;

    ftxui::Component renderer;
    ftxui::Component inputs;

    Controls(){};

    void init(
        Tetris::Config::Controls                    &controls,
        std::function<void(Tetris::Engine::Trigger)> changeKeyHandler,
        std::function<void()>                        backButtonHandler
    );
};
} // namespace Tetris::Menu