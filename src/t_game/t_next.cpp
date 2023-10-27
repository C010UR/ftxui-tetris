#include "t_game/t_next.hpp"

namespace Tetris::Game
{

void Next::checkBag()
{
    if (!bag.size() || this->index == (int)this->bag.size())
    {
        this->bag   = TetrominoFactory::getBag();
        this->index = 0;
    }
}

Next::Next()
{
    this->bag   = TetrominoFactory::getBag();
    this->index = 0;
}

Tetromino Next::pop()
{
    Tetromino next = this->bag[this->index];

    this->index++;
    this->checkBag();

    return next;
}

ftxui::Element Next::getElement()
{
    ftxui::Canvas canvas = Tetris::Renderer::Canvas::create(5, 4);

    Tetris::Renderer::Canvas::drawTetromino(canvas, this->bag[this->index], true);

    return ftxui::window(ftxui::text("Next"), ftxui::canvas(canvas));
}
} // namespace Tetris::Game