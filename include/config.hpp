#pragma once

#include <cctype>
#include <ftxui/component/event.hpp>
#include <stdio.h>
#include <string>

#include "enums.hpp"

namespace Tetris
{
class Config
{
  private:
    bool isCharacter(ftxui::Event event, std::string character)
    {
        return event == ftxui::Event::Character(character)
               || (character.size() == 1 && std::isalpha(character[0])
                   && event == ftxui::Event::Character((char)std::toupper(character[0])));
    }

  public:
    int   isDebug;
    int   isEasyMode;
    int    storeDelay;
    int    softDropDelay;
    int    comboDelay;
    double updatesPerSecond;
    int    level;

    std::string keyMoveLeft;
    std::string keyMoveRight;
    std::string keyRotateLeft;
    std::string keyRotateRight;
    std::string keySwapHold;
    std::string keySoftDrop;
    std::string keyHardDrop;
    std::string keyForfeit;

    Config()
    {
        this->isDebug          = false;
        this->isEasyMode       = true;
        this->storeDelay       = 500;
        this->softDropDelay    = 50;
        this->comboDelay       = 6000;
        this->updatesPerSecond = 240.;
        this->level            = 1;

        this->keyMoveLeft    = "a";
        this->keyMoveRight   = "d";
        this->keyRotateLeft  = ",";
        this->keyRotateRight = ".";
        this->keySwapHold    = "z";
        this->keySoftDrop    = "s";
        this->keyHardDrop    = " ";
        this->keyForfeit     = "t";
    }

    Tetris::TriggerType handleEvent(ftxui::Event event)
    {
        if (this->isCharacter(event, this->keyMoveLeft))
        {
            return Tetris::TriggerType::MOVE_LEFT;
        }

        if (this->isCharacter(event, this->keyMoveRight))
        {
            return Tetris::TriggerType::MOVE_RIGHT;
        }

        if (this->isCharacter(event, this->keyRotateLeft))
        {
            return Tetris::TriggerType::ROTATE_LEFT;
        }

        if (this->isCharacter(event, this->keyRotateRight))
        {
            return Tetris::TriggerType::ROTATE_RIGHT;
        }

        if (this->isCharacter(event, this->keySwapHold))
        {
            return Tetris::TriggerType::SWAP_HOLD;
        }

        if (this->isCharacter(event, this->keySoftDrop))
        {
            return Tetris::TriggerType::SOFT_DROP;
        }

        if (this->isCharacter(event, this->keyHardDrop))
        {
            return Tetris::TriggerType::HARD_DROP;
        }

        if (this->isCharacter(event, this->keyForfeit))
        {
            return Tetris::TriggerType::FORFEIT;
        }

        return Tetris::TriggerType::NO_TRIGGER;
    }
};
} // namespace Tetris