#pragma once

namespace Tetris
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

enum class BlockType
{
    NIL,
    PVT,
    BLK
};

enum class RotationType
{
    NO_ROTATE,
    LEFT,
    RIGHT
};

enum class TriggerType
{
    MOVE_LEFT,
    MOVE_RIGHT,
    SOFT_DROP,
    HARD_DROP,
    ROTATE_LEFT,
    ROTATE_RIGHT,
    SWAP_HOLD,
    FORFEIT,
    NO_TRIGGER
};

enum class TSpinType
{
    T_SPIN_FULL,
    T_SPIN_MINI,
    T_SPIN_NONE
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

enum class Menus
{
    MAIN_MENU,
    GAME_OVER,
    OPTIONS,
    CONTROLS
};

enum class MenuExitCodes
{
    START_GAME  = 2,
    EXIT_GAME   = 3
};
} // namespace Tetris