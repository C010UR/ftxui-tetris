#include "t_game/t_hold.hpp"

namespace Tetris::Game
{
Hold::Hold()
{
    this->current->reset();
    this->isBlocked = false;
}

Tetromino Hold::get()
{
    return this->current.value();
}

void Hold::set(Tetromino tetromino)
{
    this->current = tetromino;
    this->current->reset();
}

bool Hold::has()
{
    return this->current.has_value();
}

void Hold::block()
{
    this->isBlocked = true;
}

void Hold::unblock()
{
    this->isBlocked = false;
}

ftxui::Element Hold::getElement()
{
    ftxui::Canvas canvas = Tetris::Renderer::Canvas::create(5, 4);

    if (this->has())
    {
        Tetris::Renderer::Canvas::drawTetromino(canvas, this->current.value(), true, this->isBlocked);
    }

    return ftxui::window(ftxui::text("Hold"), ftxui::canvas(canvas));
}

} // namespace Tetris::Game