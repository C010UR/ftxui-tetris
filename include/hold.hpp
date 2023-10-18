#pragma once

#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
#include <optional>
#include <vector>

#include "canvas.hpp"
#include "tetromino.hpp"
#include "tetromino_factory.hpp"

namespace Tetris
{
class Hold
{
  private:
    std::optional<Tetris::Tetromino> hold;

  public:
    Hold() {
        this->hold.reset();
    }

    void swapHold(Tetris::Tetromino *tetromino)
    {
        if (!this->hasHold())
        {
            this->hold = *tetromino;
            tetromino  = nullptr;

            return;
        }

        Tetromino hold = this->hold.value();

        this->hold = *tetromino;
        tetromino  = &hold;
    }

    bool hasHold()
    {
        return this->hold.has_value();
    }

    ftxui::Element getElement()
    {
        ftxui::Canvas canvas = Tetris::Canvas::createCanvas(5, 5);

        if (this->hasHold())
        {
            Tetris::Canvas::drawTetromino(canvas, this->hold.value(), false);
        }

        return ftxui::window(ftxui::text("Hold"), ftxui::canvas(canvas));
    }
};
} // namespace Tetris