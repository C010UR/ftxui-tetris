#pragma once

#include "ftxui/dom/canvas.hpp"
#include "t_game/t_tetromino.hpp"
#include "t_renderer/t_current_theme.hpp"

#include <cmath>
#include <string>

namespace Tetris::Renderer {
class Canvas
{
  public:
    inline static const int         stepX             = 4;
    inline static const int         stepY             = 4;
    inline static const std::string blockSymbol       = "██";
    inline static const std::string shadowBlockSymbol = "░░";

    static void drawTetromino(
        ftxui::Canvas          &canvas,
        Tetris::Game::Tetromino tetromino,
        bool                    isCentered = false,
        bool                    isShadow   = false);

    static void drawBoard(
        ftxui::Canvas                                         &canvas,
        std::vector<std::vector<Tetris::Game::BoardBlockType>> board,
        std::vector<std::vector<ftxui::Color>>                 boardColor);

    static void drawBlock(
        ftxui::Canvas              &canvas,
        int                         x,
        int                         y,
        ftxui::Color                color,
        bool                        isCentered    = false,
        bool                        isShadow      = false,
        Tetris::Game::TetrominoType tetrominoType = Tetris::Game::TetrominoType::T);

    static ftxui::Canvas create(int width, int height);
};
} // namespace Tetris::Renderer