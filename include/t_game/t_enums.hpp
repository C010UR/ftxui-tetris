#pragma once

#include <vector>
namespace Tetris::Game
{
enum class TetrominoType
{
    I,
    O,
    T,
    J,
    L,
    S,
    Z
};

enum class BoardBlockType
{
    NONE  = 0,
    BLOCK = 1
};

enum class BlockType
{
    NONE              = 0,
    BLOCK             = 1,
    SPIN_LOOKUP_FRONT = 2,
    SPIN_LOOKUP_BACK  = 3
};

enum class RotationType
{
    NONE,
    LEFT,
    RIGHT
};

enum class SpinType
{
    NONE,
    T_SPIN_FULL,
    T_SPIN_MINI,
};

enum class ScoreType
{
    SINGLE,
    DOUBLE,
    TRIPLE,
    TETRIS,
    MINI_T_SPIN_NO_LINES,
    T_SPIN_NO_LINES,
    MINI_T_SPIN_SINGLE,
    T_SPIN_SINGLE,
    MINI_T_SPIN_DOUBLE,
    T_SPIN_DOUBLE,
    T_SPIN_TRIPLE,
    SOFT_DROP,
    HARD_DROP,
    SINGLE_LINE_PERFECT_CLEAR,
    DOUBLE_LINE_PERFECT_CLEAR,
    TRIPLE_LINE_PERFECT_CLEAR,
    TETRIS_LINE_PERFECT_CLEAR,
    NONE
};

typedef std::vector<std::vector<Tetris::Game::BoardBlockType>> board_t;
typedef std::vector<std::vector<Tetris::Game::BlockType>> tetromino_t;
typedef std::vector<tetromino_t> tetromino_rotations_t;
} // namespace Tetris::Game