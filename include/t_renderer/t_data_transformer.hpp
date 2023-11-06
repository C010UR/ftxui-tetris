#pragma once

#include "ftxui/screen/color.hpp"
#include "t_game/t_enums.hpp"

#include <cctype>
#include <iomanip>
#include <ios>
#include <sstream>
#include <string>

namespace Tetris::Renderer {
class DataTransformer
{
  public:
    static std::string transformKey(std::string key);

    static std::string toString(Tetris::Game::ScoreType type);
    static std::string toString(Tetris::Game::TetrominoType type);
    static std::string toString(Tetris::Game::SpinType type);
    static std::string toString(Tetris::Game::RotationType type);
    static std::string toString(ftxui::Color color);
    static char        toString(Tetris::Game::BlockType type);

    static int transformRotation(int rotation);
};
} // namespace Tetris::Renderer