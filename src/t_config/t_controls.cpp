#include "t_config/t_controls.hpp"

#include "t_engine/t_enums.hpp"

namespace Tetris::Config {
bool Controls::isCharacter(ftxui::Event event, std::string character)
{
    if (character.size() == 1 && std::isalpha(character[0])) {
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
    this->retry       = "r";
}

std::string Controls::transformEvent(ftxui::Event event)
{
    return event.character().size() == 1 && std::isalpha(event.character()[0])
               ? std::string(1, std::tolower(event.character()[0]))
               : event.character();
}

Tetris::Engine::Trigger Controls::handleEvent(ftxui::Event event)
{
    std::string character = Controls::transformEvent(event);

    if (this->moveLeft == character) {
        return Tetris::Engine::Trigger::KEY_MOVE_LEFT;
    }

    if (this->moveRight == character) {
        return Tetris::Engine::Trigger::KEY_MOVE_RIGHT;
    }

    if (this->rotateLeft == character) {
        return Tetris::Engine::Trigger::KEY_ROTATE_LEFT;
    }

    if (this->rotateRight == character) {
        return Tetris::Engine::Trigger::KEY_ROTATE_RIGHT;
    }

    if (this->swapHold == character) {
        return Tetris::Engine::Trigger::KEY_SWAP_HOLD;
    }

    if (this->softDrop == character) {
        return Tetris::Engine::Trigger::KEY_SOFT_DROP;
    }

    if (this->hardDrop == character) {
        return Tetris::Engine::Trigger::KEY_HARD_DROP;
    }

    if (this->forfeit == character) {
        return Tetris::Engine::Trigger::KEY_FORFEIT;
    }

    if (this->retry == character) {
        return Tetris::Engine::Trigger::KEY_RETRY;
    }

    return Tetris::Engine::Trigger::NONE;
}

void Controls::changeKey(Tetris::Engine::Trigger trigger, std::string key)
{
    switch (trigger) {
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
        case Engine::Trigger::KEY_RETRY:
            this->retry = key;
            break;
        default:
            break;
    }
}
} // namespace Tetris::Config
