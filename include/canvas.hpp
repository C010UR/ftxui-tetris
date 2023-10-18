#pragma once

#include <ftxui/dom/canvas.hpp>
#include <string>
#include <vector>

#include "ftxui/screen/color.hpp"
#include "tetromino.hpp"

namespace Tetris
{
class Canvas
{
  public:

    inline static const int         stepX             = 4;
    inline static const int         stepY             = 4;
    inline static const std::string blockSymbol       = "██";
    inline static const std::string shadowBlockSymbol = "░░";

    static void drawTetromino(
        ftxui::Canvas &canvas, Tetris::Tetromino tetromino, bool isDefault = false, bool isShadow = false
    )
    {
        auto data = tetromino.getMatrix();

        if (isDefault)
        {
            data = tetromino.getMatrix(0);
        }

        for (int i = 0; i < (int)data.size(); i++)
        {
            for (int j = 0; j < (int)data[i].size(); j++)
            {
                if (data[i][j] == Tetris::BlockType::NIL)
                {
                    continue;
                }

                Tetris::Canvas::drawBlock(
                    canvas,
                    (!isDefault ? tetromino.getX() : 1) + j,
                    (!isDefault ? tetromino.getY() : 1) + i,
                    tetromino.getColor(),
                    isShadow,
                    isDefault && tetromino.isEven()
                );
            }
        }
    }

    static void drawBoard(
        ftxui::Canvas &canvas, std::vector<std::vector<bool>> board, std::vector<std::vector<ftxui::Color>> boardColor
    )
    {
        for (int i = 0; i < (int)board.size(); i++)
        {
            for (int j = 0; j < (int)board[i].size(); j++)
            {
                if (board[i][j])
                {
                    Tetris::Canvas::drawBlock(canvas, j, i, boardColor[i][j]);
                }
            }
        }
    }

    static void drawBlock(
        ftxui::Canvas &canvas, int x, int y, ftxui::Color color, bool isShadow = false, bool isDrawEven = false
    )
    {
        canvas.DrawText(
            x * stepX - (isDrawEven ? stepX / 2 : 0),
            y * stepY,
            isShadow ? shadowBlockSymbol : blockSymbol,
            [&](ftxui::Pixel &p) {
                p.foreground_color = color;
                if (!isShadow)
                {
                    p.background_color = color;
                }
            }
        );
    }

    static ftxui::Canvas createCanvas(int width, int height)
    {
        return ftxui::Canvas(width * stepX, height * stepY);
    }
};
} // namespace Tetris