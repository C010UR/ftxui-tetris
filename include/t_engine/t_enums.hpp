#pragma once

namespace Tetris::Engine
{
enum class Trigger
{
    NONE,
    KEY_MOVE_LEFT,
    KEY_MOVE_RIGHT,
    KEY_ROTATE_LEFT,
    KEY_ROTATE_RIGHT,
    KEY_SWAP_HOLD,
    KEY_SOFT_DROP,
    KEY_HARD_DROP,
    KEY_FORFEIT
};
} // namespace Tetris::Engine