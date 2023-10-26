#include "t_config/t_controls.hpp"

namespace Tetris::Config
{
bool Controls::isCharacter(ftxui::Event event, std::string character)
{
    if (character.size() == 1 && std::isalpha(character[0]))
    {
        return event == ftxui::Event::Character((char)std::tolower(character[0]))
               || event == ftxui::Event::Character((char)std::toupper(character[0]));
    }

    return event == ftxui::Event::Character(character);
}

Controls::Controls()
{
    this->moveLeft    = "a";
    this->moveRight   = "d";
    this->rotateLeft  = ",";
    this->rotateRight = ".";
    this->swapHold    = "z";
    this->softDrop    = "s";
    this->hardDrop    = " ";
    this->forfeit     = "t";
}

Tetris::Engine::Trigger Controls::handleEvent(ftxui::Event event)
{
    if (this->isCharacter(event, this->moveLeft))
    {
        return Tetris::Engine::Trigger::KEY_MOVE_LEFT;
    }

    if (this->isCharacter(event, this->moveRight))
    {
        return Tetris::Engine::Trigger::KEY_MOVE_RIGHT;
    }

    if (this->isCharacter(event, this->rotateLeft))
    {
        return Tetris::Engine::Trigger::KEY_ROTATE_LEFT;
    }

    if (this->isCharacter(event, this->rotateRight))
    {
        return Tetris::Engine::Trigger::KEY_ROTATE_RIGHT;
    }

    if (this->isCharacter(event, this->swapHold))
    {
        return Tetris::Engine::Trigger::KEY_SWAP_HOLD;
    }

    if (this->isCharacter(event, this->softDrop))
    {
        return Tetris::Engine::Trigger::KEY_SOFT_DROP;
    }

    if (this->isCharacter(event, this->hardDrop))
    {
        return Tetris::Engine::Trigger::KEY_HARD_DROP;
    }

    if (this->isCharacter(event, this->forfeit))
    {
        return Tetris::Engine::Trigger::KEY_FORFEIT;
    }

    return Tetris::Engine::Trigger::NONE;
}

void Controls::changeKey(Tetris::Engine::Trigger trigger, std::string key)
{
    switch (trigger)
    {
    case Engine::Trigger::KEY_MOVE_LEFT:
        this->moveLeft = key;
        break;
    case Engine::Trigger::KEY_MOVE_RIGHT:
        this->moveRight = key;
        break;
    case Engine::Trigger::KEY_ROTATE_LEFT:
        this->rotateLeft = key;
        break;
    case Engine::Trigger::KEY_ROTATE_RIGHT:
        this->rotateRight = key;
        break;
    case Engine::Trigger::KEY_SWAP_HOLD:
        this->swapHold = key;
        break;
    case Engine::Trigger::KEY_SOFT_DROP:
        this->softDrop = key;
        break;
    case Engine::Trigger::KEY_HARD_DROP:
        this->hardDrop = key;
        break;
    case Engine::Trigger::KEY_FORFEIT:
        this->forfeit = key;
        break;
    default:
        break;
    }
}
} // namespace Tetris::Config