#pragma once

#include "t_config/t_theme.hpp"

#include <vector>

namespace Tetris::Config
{
class Config
{
  public:

    int    isDebug;
    int    isEasyMode;
    int    storeDelay;
    int    softDropDelay;
    int    comboDelay;
    double updatesPerSecond;
    int    level;

    std::vector<Tetris::Config::Theme> themes;

    int currentTheme;

    Config();

    void nextTheme();
    void prevTheme();
    void applyTheme();
};
} // namespace Tetris::Config