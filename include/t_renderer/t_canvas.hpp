#pragma once

#include "ftxui/dom/canvas.hpp"
#include "t_game/t_enums.hpp"
#include "t_game/t_tetromino.hpp"
#include "t_renderer/t_current_theme.hpp"

#include <cmath>
#include <string>

namespace Tetris::Renderer {
class Canvas
{
    inline static const int         stepX             = 4;
    inline static const int         stepY             = 4;
    inline static const std::string blockSymbol       = "██";
    inline static const std::string shadowBlockSymbol = "░░";

  public:
    static void drawTetromino(
        ftxui::Canvas          &canvas,
        Tetris::Game::Tetromino tetromino,
        bool                    isCentered = false,
        bool                    isShadow   = false,
        int                     offset     = 0);

    static void drawBoard(
        ftxui::Canvas                         &canvas,
        Game::board_t                          board,
        Game::board_color_t boardColor,
        int                                    offset);

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