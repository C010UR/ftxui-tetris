#pragma once

#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/color.hpp"
#include "t_config/t_controls.hpp"
#include "t_engine/t_enums.hpp"
#include "t_renderer/t_current_theme.hpp"
#include "t_renderer/t_header.hpp"

#include <cctype>
#include <functional>
#include <vector>

namespace Tetris::Menu
{
class ChangeKey
{
  public:

    Tetris::Config::Controls *controls;

    bool                    isModalOpen;
    Tetris::Engine::Trigger trigger;

    ftxui::Component renderer;

    ChangeKey() : isModalOpen(false), trigger(Tetris::Engine::Trigger::NONE){};

    void init(Tetris::Config::Controls &controls);
    bool handleEvent(ftxui::Event event);

    ChangeKey &operator=(const ChangeKey &other);
};
} // namespace Tetris::Menu
