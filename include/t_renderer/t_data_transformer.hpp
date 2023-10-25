#pragma once

#include "t_game/t_enums.hpp"

#include <cctype>
#include <string>

namespace Tetris::Renderer
{
class DataTransformer
{
  public:

    static std::string transformKey(std::string key);

    static std::string toString(Tetris::Game::ScoreType type);
    static std::string toString(Tetris::Game::TetrominoType type);

    static int transformRotation(int rotation);
};
} // namespace Tetris::Renderer