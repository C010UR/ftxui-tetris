#include "t_config/t_config.hpp"

namespace Tetris::Config
{
Config::Config()
{
    this->isDebug          = false;
    this->isEasyMode       = true;
    this->storeDelay       = 500;
    this->softDropDelay    = 50;
    this->comboDelay       = 6000;
    this->updatesPerSecond = 240.;
    this->softDropGravity  = 50.;
    this->level            = 1;

    Tetris::Config::Theme defaultTheme;

    defaultTheme.setDefault();

    this->themes       = {defaultTheme};
    this->currentTheme = 0;
}

void Config::nextTheme()
{
    if (this->currentTheme == (int)this->themes.size() - 1)
    {
        this->currentTheme = 0;
    }
    else
    {
        this->currentTheme++;
    }
}

void Config::prevTheme()
{
    if (this->currentTheme == 0)
    {
        this->currentTheme = (int)this->themes.size() - 1;
    }
    else
    {
        this->currentTheme--;
    }
}

void Config::applyTheme()
{
    if (this->themes.empty())
    {
        return;
    }

    this->themes[this->currentTheme].apply();
}
} // namespace Tetris::Config