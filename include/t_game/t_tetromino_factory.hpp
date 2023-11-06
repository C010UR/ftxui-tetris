#pragma once

#include "t_game/t_enums.hpp"
#include "t_game/t_point.hpp"
#include "t_game/t_tetromino.hpp"
#include "t_renderer/t_current_theme.hpp"

#include <algorithm>
#include <random>
#include <vector>

namespace Tetris::Game {
class TetrominoFactory
{
  private:
    static std::vector<std::vector<Point>> OWallKickData;
    static std::vector<std::vector<Point>> IWallKickData;
    static std::vector<std::vector<Point>> JLTSZWallKickData;

    static std::vector<std::vector<std::vector<BlockType>>> I;
    static std::vector<std::vector<std::vector<BlockType>>> O;
    static std::vector<std::vector<std::vector<BlockType>>> T;
    static std::vector<std::vector<std::vector<BlockType>>> L;
    static std::vector<std::vector<std::vector<BlockType>>> J;
    static std::vector<std::vector<std::vector<BlockType>>> S;
    static std::vector<std::vector<std::vector<BlockType>>> Z;

  public:
    static Tetromino              get(TetrominoType type);
    static std::vector<Tetromino> getBag();
};
} // namespace Tetris::Game