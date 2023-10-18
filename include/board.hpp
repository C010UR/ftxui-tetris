#pragma once

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/task.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>
#include <optional>
#include <processthreadsapi.h>
#include <string>
#include <vector>

#include "canvas.hpp"
#include "tetromino.hpp"
#include "tetromino_factory.hpp"

namespace Tetris
{
class Board
{
  private:
    std::vector<std::vector<ftxui::Color>> boardColor;
    std::vector<std::vector<bool>>         board;

    Tetris::Tetromino current;

  public:
    inline static const int width  = 10;
    inline static const int height = 20;

    Board()
    {
    }

    Board(Tetris::Tetromino tetromino)

    {
        this->board.clear();
        this->boardColor.clear();

        for (int i = 0; i < height; i++)
        {
            this->board.push_back(std::vector<bool>(width, false));
            this->boardColor.push_back(std::vector<ftxui::Color>(width, ftxui::Color::Default));
        }

        this->current = tetromino;
    }

    Tetris::Tetromino getCurrent()
    {
        return this->current;
    }

    void setCurrent(Tetris::Tetromino tetromino)
    {
        this->current = tetromino;
        this->current.move((this->width - 1) / 2, 0);
    }

    bool canMove(int x, int y, int rotation)
    {
        if (!this->board.size() || !this->board[0].size())
        {
            return false;
        }

        auto tetromino = this->current;

        int currentRotation = tetromino.getRotation();

        switch (rotation)
        {
        case Tetris::RotationType::LEFT:
            currentRotation = tetromino.rotateLeft(currentRotation);
            break;
        case Tetris::RotationType::RIGHT:
            currentRotation = tetromino.rotateRight(currentRotation);
            break;
        default:
            break;
        }

        auto data = tetromino.get(currentRotation);

        if (!data.size() || !data[0].size())
        {
            return false;
        }

        for (int i = 0; i < (int)data.size(); i++)
        {
            for (int j = 0; j < (int)data[0].size(); j++)
            {
                if (data[i][j] == Tetris::BlockType::NIL)
                {
                    continue;
                }

                int currentX = tetromino.getX() + x + j;
                int currentY = tetromino.getY() + y + i;

                if (currentX < 0 || currentX + 1 > (int)this->board[0].size())
                {
                    return false;
                }

                if (currentY < 0 || currentY + 1 > (int)this->board.size())
                {
                    return false;
                }

                if (this->board[currentY][currentX])
                {
                    return false;
                }
            }
        }

        return true;
    }

    // void              store(Tetris::Tetromino tetromino);
    // void              updateLines(Tetris::Score score);

    ftxui::Element getDebugElement()
    {
        return ftxui::vbox({ftxui::window(
            ftxui::text("Tetromino"),
            ftxui::vbox(
                {ftxui::hbox({
                     ftxui::text("X: "),
                     ftxui::text(std::to_string(this->current.getX())) | ftxui::color(ftxui::Color::Yellow1),
                 }),
                 ftxui::hbox({
                     ftxui::text("Y: "),
                     ftxui::text(std::to_string(this->current.getY())) | ftxui::color(ftxui::Color::Yellow1),
                 }),
                 ftxui::hbox({
                     ftxui::text("Color: "),
                     ftxui::text("<color>") | ftxui::color(this->current.getColor()),
                 })}
            )
        )});
    }

    ftxui::Element getBoardElement()
    {
        ftxui::Canvas canvas = Tetris::Canvas::createCanvas(this->width, this->height);

        Tetris::Canvas::drawBoard(canvas, this->board, this->boardColor);
        Tetris::Canvas::drawTetromino(canvas, this->current, false);

        return ftxui::canvas(canvas) | ftxui::border;
    }
};
} // namespace Tetris
