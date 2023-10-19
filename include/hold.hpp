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
    
    bool blocked;

  public:
    Hold() {
        this->hold.reset();
        this->blocked = false;
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
        ftxui::Canvas canvas = Tetris::Canvas::createCanvas(5, 4);

        if (this->hasHold())
        {
            Tetris::Canvas::drawTetromino(canvas, this->hold.value(), true, this->blocked);
        }

        return ftxui::window(ftxui::text("Hold"), ftxui::canvas(canvas));
    }

    void block()
    {
        this->blocked = true;
    }

    void unblock()
    {
        this->blocked = false;
    }

    bool isBlocked()
    {
        return this->blocked;
    }
};
} // namespace Tetris