#pragma once

#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
#include <vector>

#include "canvas.hpp"
#include "tetromino.hpp"
#include "tetromino_factory.hpp"

namespace Tetris
{
class Next
{
  private:
    std::vector<Tetris::Tetromino> bag;

    int index;

    void validateBag()
    {
        if (!bag.size() || this->index == (int)this->bag.size())
        {
            this->bag   = Tetris::TetrominoFactory::generateBag();
            this->index = 0;
        }
    }

  public:
    Next()
    {
        this->bag   = Tetris::TetrominoFactory::generateBag();
        this->index = 0;
    }

    Tetris::Tetromino pop()
    {
        Tetris::Tetromino next = this->bag[this->index];
        this->index++;

        this->validateBag();

        return next;
    }

    ftxui::Element getElement()
    {
        ftxui::Canvas canvas = Tetris::Canvas::createCanvas(5, 4);

        Tetris::Canvas::drawTetromino(canvas, this->bag[this->index], true);

        return ftxui::window(ftxui::text("Next"), ftxui::canvas(canvas));
    }
};
} // namespace Tetris