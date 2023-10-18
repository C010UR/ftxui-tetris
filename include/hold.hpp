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

    void setHold(Tetris::Tetromino tetromino)
    {
        this->hold = tetromino;
    }

    Tetris::Tetromino getHold()
    {
        return this->hold.value();
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
            Tetris::Canvas::drawTetromino(canvas, this->hold.value(), true);
        }

        return ftxui::window(ftxui::text("Hold"), ftxui::canvas(canvas));
    }
};
} // namespace Tetris