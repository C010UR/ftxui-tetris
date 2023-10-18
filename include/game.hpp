#pragma once

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
#include <vector>

#include "board.hpp"
#include "canvas.hpp"
#include "hold.hpp"
#include "next.hpp"
#include "score.hpp"
#include "tetromino.hpp"

namespace Tetris
{
class Game
{
  private:
    Tetris::Board board;
    Tetris::Score score;
    Tetris::Next  next;
    Tetris::Hold  hold;

  public:
    Game()
    {
        this->score = Tetris::Score();
        this->next  = Tetris::Next();
        this->hold  = Tetris::Hold();
        this->board = Tetris::Board(this->next.pop());
    }

    bool handleEvent(ftxui::Event event)
    {
        auto tetromino = this->board.getCurrent();

        int                  x        = 0;
        int                  y        = 0;
        Tetris::RotationType rotation = Tetris::RotationType::NO_ROTATE;

        if (event == ftxui::Event::Character('d'))
        {
            x = 1;
        }

        if (event == ftxui::Event::Character('a'))
        {
            x = -1;
        }

        if (event == ftxui::Event::Character(' '))
        {
            while (this->board.canMove(x, y++, rotation))
                ;
        }

        if (event == ftxui::Event::Character('s'))
        {
            y += 1;
        }

        if (this->board.canMove(x, y, rotation)) {
          this->board.getCurrent().move(x, y);
          this->board.getCurrent().rotate(rotation);
        }

        return false;
    }

    ftxui::Component getRenderer(bool debug = false)
    {
        return ftxui::Renderer([debug, this] {
            std::vector<ftxui::Element> elements;

            elements.push_back(this->board.getBoardElement());

            elements.push_back(ftxui::vbox(
                {this->next.getElement(),
                 this->score.getElement(),
                 ftxui::canvas(Tetris::Canvas::createCanvas(5, 5)),
                 this->hold.getElement()}
            ));

            if (debug)
            {
                elements.push_back(this->board.getDebugElement());
            }

            return ftxui::hbox(elements);
        });
    }
};
} // namespace Tetris