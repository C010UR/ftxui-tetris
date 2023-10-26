#include "t_renderer/t_data_transformer.hpp"

namespace Tetris::Renderer
{
std::string DataTransformer::transformKey(std::string key)
{
    if (key == "\x1B[D")
    {
        return "←";
    }
    if (key == "\x1B[C")
    {
        return "→";
    }
    if (key == "\x1B[A")
    {
        return "↑";
    }
    if (key == "\x1B[B")
    {
        return "↓";
    }
    if (key == "\x1B[1;5D")
    {
        return "Ctrl + ←";
    }
    if (key == "\x1B[1;5C")
    {
        return "Ctrl + →";
    }
    if (key == "\x1B[1;5A")
    {
        return "Ctrl + ↑";
    }
    if (key == "\x1B[1;5B")
    {
        return "Ctrl + ↓";
    }
    if (key == std::string({127}))
    {
        return "Backspace";
    }
    if (key == "\x1B[3~")
    {
        return "Delete";
    }
    if (key == "\x1B")
    {
        return "Escape";
    }
    if (key == std::string({10}))
    {
        return "Return";
    }
    if (key == std::string({9}))
    {
        return "Tab";
    }
    if (key == std::string({27, 91, 90}))
    {
        return "Shift + Tab";
    }

    if (key == "\x1BOP")
    {
        return "F1";
    }
    if (key == "\x1BOQ")
    {
        return "F2";
    }
    if (key == "\x1BOR")
    {
        return "F3";
    }
    if (key == "\x1BOS")
    {
        return "F4";
    }
    if (key == "\x1B[15~")
    {
        return "F5";
    }
    if (key == "\x1B[17~")
    {
        return "F6";
    }
    if (key == "\x1B[18~")
    {
        return "F7";
    }
    if (key == "\x1B[19~")
    {
        return "F8";
    }
    if (key == "\x1B[20~")
    {
        return "F9";
    }
    if (key == "\x1B[21~")
    {
        return "F10";
    }
    if (key == "\x1B[23~")
    {
        return "F11";
    }
    if (key == "\x1B[24~")
    {
        return "F12";
    }

    if (key == std::string({27, 91, 72}))
    {
        return "Home";
    }
    if (key == std::string({27, 91, 70}))
    {
        return "End";
    }
    if (key == std::string({27, 91, 53, 126}))
    {
        return "PageUp";
    }
    if (key == std::string({27, 91, 54, 126}))
    {
        return "PageDown";
    }

    return key;
}

std::string DataTransformer::toString(Tetris::Game::ScoreType type)
{
    switch (type)
    {
    case Tetris::Game::ScoreType::SINGLE:
        return "Single";
    case Tetris::Game::ScoreType::DOUBLE:
        return "Double";
    case Tetris::Game::ScoreType::TRIPLE:
        return "Triple";
    case Tetris::Game::ScoreType::TETRIS:
        return "TETRIS";
    case Tetris::Game::ScoreType::MINI_T_SPIN_NO_LINES:
        return "Mini T-Spin";
    case Tetris::Game::ScoreType::T_SPIN_NO_LINES:
        return "T-Spin";
    case Tetris::Game::ScoreType::MINI_T_SPIN_SINGLE:
        return "Mini T-Spin Single";
    case Tetris::Game::ScoreType::T_SPIN_SINGLE:
        return "T-Spin Single";
    case Tetris::Game::ScoreType::MINI_T_SPIN_DOUBLE:
        return "Mini T-Spin Double";
    case Tetris::Game::ScoreType::T_SPIN_DOUBLE:
        return "T-Spin Double";
    case Tetris::Game::ScoreType::T_SPIN_TRIPLE:
        return "T-Spin Triple";
    case Tetris::Game::ScoreType::SOFT_DROP:
        return "Soft Drop";
    case Tetris::Game::ScoreType::HARD_DROP:
        return "Hard Drop";
    case Tetris::Game::ScoreType::SINGLE_LINE_PERFECT_CLEAR:
        return "Perfect Clear";
    case Tetris::Game::ScoreType::DOUBLE_LINE_PERFECT_CLEAR:
        return "Perfect Clear Double";
    case Tetris::Game::ScoreType::TRIPLE_LINE_PERFECT_CLEAR:
        return "Perfect Clear Triple";
    case Tetris::Game::ScoreType::TETRIS_LINE_PERFECT_CLEAR:
        return "Perfect Clear TETRIS";
    default:
        return "None";
    }
}

std::string DataTransformer::toString(Tetris::Game::TetrominoType type)
{
    switch (type)
    {

    case Tetris::Game::TetrominoType::I:
        return "I";
    case Tetris::Game::TetrominoType::O:
        return "O";
    case Tetris::Game::TetrominoType::T:
        return "T";
    case Tetris::Game::TetrominoType::J:
        return "J";
    case Tetris::Game::TetrominoType::L:
        return "L";
    case Tetris::Game::TetrominoType::S:
        return "S";
    case Tetris::Game::TetrominoType::Z:
        return "Z";
    default:
        return "None";
    }
}

int DataTransformer::transformRotation(int rotation)
{
    switch (rotation)
    {
    case 1:
        return 90;
    case 2:
        return 180;
    case 3:
        return 270;
    default:
        return 0;
    }
}

std::string DataTransformer::toString(Tetris::Game::SpinType type)
{
    switch (type)
    {
    case Game::SpinType::T_SPIN_FULL:
        return "T-Spin";
    case Game::SpinType::T_SPIN_MINI:
        return "Mini T-Spin";
    default:
        return "None";
    }
}

std::string DataTransformer::toString(Tetris::Game::RotationType type)
{
    switch (type)
    {
    case Game::RotationType::LEFT:
        return "Left";
    case Game::RotationType::RIGHT:
        return "Right";
    default:
        return "None";
    }
}
char DataTransformer::toString(Tetris::Game::BlockType type)
{
    switch (type)
    {
    case Game::BlockType::BLOCK:
        return 'O';
    case Game::BlockType::SPIN_LOOKUP_FRONT:
        return '+';
    case Game::BlockType::SPIN_LOOKUP_BACK:
        return '-';
    default:
        return ' ';
        break;
    }
}

std::string DataTransformer::toString(ftxui::Color color)
{
    uint8_t red, green, blue;

    ftxui::Color::getColor(color, &red, &green, &blue);

    std::stringstream ss;

    ss << std::hex << std::setfill('0');
    ss << '#' << std::setw(2) << static_cast<int>(red) << std::setw(2) << static_cast<int>(green) << std::setw(2)
       << static_cast<int>(blue);

    return ss.str();
}
} // namespace Tetris::Renderer