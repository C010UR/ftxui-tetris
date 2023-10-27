#pragma once

#include "ftxui/component/event.hpp"
#include "t_engine/t_enums.hpp"

#include <cctype>
#include <string>

namespace Tetris::Config
{
class Controls
{
  private:

    bool isCharacter(ftxui::Event event, std::string character);

  public:

    std::string moveLeft;
    std::string moveRight;
    std::string rotateLeft;
    std::string rotateRight;
    std::string swapHold;
    std::string softDrop;
    std::string hardDrop;
    std::string forfeit;
    std::string retry;

    Controls();

    Tetris::Engine::Trigger handleEvent(ftxui::Event event);

    void changeKey(Tetris::Engine::Trigger trigger, std::string key);
};
} // namespace Tetris::Config