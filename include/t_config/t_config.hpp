#pragma once

#include "ftxui/screen/color.hpp"
#include "t_config/t_theme.hpp"

#include <vector>

namespace Tetris::Config {
class Config
{
  public:
    bool isDebug;
    bool isEasyMode;

    bool withBackgroundColor;

    int storeDelay;
    int softDropDelay;
    int comboDelay;

    double fps;
    double updatesPerSecond;
    double softDropGravity;

    int level;

    std::vector<Theme> themes;

    int currentTheme;

    Config();

    void nextTheme();
    void prevTheme();
    void applyTheme();
};
} // namespace Tetris::Config