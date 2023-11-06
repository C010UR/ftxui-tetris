#pragma once

#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/dom/node.hpp"
#include "t_renderer/t_current_theme.hpp"
#include "t_renderer/t_data_transformer.hpp"

#include <iomanip>
#include <sstream>

namespace Tetris::Menu {
class MenuHelper
{
  public:
    static ftxui::Component getAsciiButton(const std::string &name, std::function<void()> function);
    static ftxui::Component
    getAnimatedButton(const std::string &name, std::function<void()> function, bool isGameOver = false);

    static ftxui::Element getOptionElement(
        const std::string      &name,
        const std::string      &value,
        const ftxui::Component &addButton,
        const ftxui::Component &subButton,
        const bool              validateAdd,
        const bool              validateSub,
        const int               width   = 15,
        const int               leftPad = 2);

    static ftxui::Element getOptionElement(
        const std::string                &name,
        const double                      value,
        const ftxui::Component           &addButton,
        const ftxui::Component           &subButton,
        const std::function<bool(double)> validateAdd,
        const std::function<bool(double)> validateSub,
        int                               width   = 15,
        int                               leftPad = 2);

    static ftxui::Element getOptionElement(
        const std::string             &name,
        const int                      value,
        const ftxui::Component        &addButton,
        const ftxui::Component        &subButton,
        const std::function<bool(int)> validateAdd,
        const std::function<bool(int)> validateSub,
        int                            width   = 15,
        int                            leftPad = 2);

    static ftxui::Element getOptionElement(
        const std::string      &name,
        const std::string      &valueString,
        const ftxui::Component &addButton,
        const ftxui::Component &subButton,
        int                     width   = 15,
        int                     leftPad = 2);

    static ftxui::Element getToggleOptionElement(
        const std::string      &name,
        const bool              value,
        const ftxui::Component &toggleButton,
        int                     width   = 15,
        int                     leftPad = 2);

    static ftxui::Element getControlsElement(
        const std::string      &name,
        const std::string      &controls,
        const ftxui::Component &button,
        int                     width   = 15,
        int                     leftPad = 2);

    static ftxui::Element getHeaderElement(const std::string &name);
    static ftxui::Element getButtonMargin(const int height = 1);
};
} // namespace Tetris::Menu