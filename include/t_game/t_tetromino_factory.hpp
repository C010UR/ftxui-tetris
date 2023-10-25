#pragma once

#include "t_game/t_enums.hpp"
#include "t_game/t_point.hpp"
#include "t_game/t_tetromino.hpp"
#include "t_renderer/t_color.hpp"

#include <algorithm>
#include <random>
#include <vector>

namespace Tetris::Game
{
class TetrominoFactory
{
  private:

    static std::vector<std::vector<Tetris::Game::Point>> OWallKickData;
    static std::vector<std::vector<Tetris::Game::Point>> IWallKickData;
    static std::vector<std::vector<Tetris::Game::Point>> JLTSZWallKickData;

    static std::vector<std::vector<std::vector<Tetris::Game::BlockType>>> I;
    static std::vector<std::vector<std::vector<Tetris::Game::BlockType>>> O;
    static std::vector<std::vector<std::vector<Tetris::Game::BlockType>>> T;
    static std::vector<std::vector<std::vector<Tetris::Game::BlockType>>> L;
    static std::vector<std::vector<std::vector<Tetris::Game::BlockType>>> J;
    static std::vector<std::vector<std::vector<Tetris::Game::BlockType>>> S;
    static std::vector<std::vector<std::vector<Tetris::Game::BlockType>>> Z;

  public:

    static Tetris::Game::Tetromino              get(Tetris::Game::TetrominoType type);
    static std::vector<Tetris::Game::Tetromino> getBag();
};
} // namespace Tetris::Game