#pragma once

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
#include <vector>

#include "board.hpp"
#include "canvas.hpp"
#include "ftxui/screen/color.hpp"
#include "hold.hpp"
#include "next.hpp"
#include "output_helper.hpp"
#include "score.hpp"
#include "tetromino.hpp"

namespace Tetris
{

class Game
{
  private:
    bool isEasyMode;

    Tetris::Board board;
    Tetris::Score score;
    Tetris::Next  next;
    Tetris::Hold  hold;

    std::string         lastInput;
    Tetris::TriggerType trigger;

  public:
    Game(bool isEasyMode = false)
    {
        this->isEasyMode = isEasyMode;

        this->score = Tetris::Score();
        this->next  = Tetris::Next();
        this->hold  = Tetris::Hold();
        this->board = Tetris::Board(this->next.pop());
    }

    bool handleEvent(ftxui::Event event)
    {
        this->lastInput = event.character();

        bool isMoveEvent   = false;
        bool isRotateEvent = false;

        int x = 0;
        int y = 0;

        if (event == ftxui::Event::Character('d') || event == ftxui::Event::Character('D'))
        {
            x = 1;

            this->trigger = Tetris::TriggerType::MOVE_RIGHT;
            isMoveEvent   = true;
        }

        if (event == ftxui::Event::Character('a') || event == ftxui::Event::Character('A'))
        {
            x = -1;

            this->trigger = Tetris::TriggerType::MOVE_LEFT;
            isMoveEvent   = true;
        }

        if (event == ftxui::Event::Character('s') || event == ftxui::Event::Character('S'))
        {
            y = 1;

            this->trigger = Tetris::TriggerType::SOFT_DROP;
            isMoveEvent   = true;
        }

        if (isMoveEvent && this->board.canMove(x, y))
        {
            this->board.getCurrent()->move(x, y);

            return true;
        }

        Tetris::RotationType rotation = Tetris::RotationType::NO_ROTATE;

        if (event == ftxui::Event::Character('.') || event == ftxui::Event::Character('>'))
        {
            rotation = Tetris::RotationType::RIGHT;

            this->trigger = Tetris::TriggerType::ROTATE_RIGHT;
            isRotateEvent = true;
        };

        if (event == ftxui::Event::Character(',') || event == ftxui::Event::Character('<'))
        {
            rotation = Tetris::RotationType::LEFT;

            this->trigger = Tetris::TriggerType::ROTATE_LEFT;
            isRotateEvent = true;
        };

        if (isRotateEvent && this->board.canRotate(x, y, rotation))
        {
            this->board.getCurrent()->move(x, y, rotation);

            return true;
        }

        if (event == ftxui::Event::Character(' '))
        {
            y = this->board.getHardDropY();

            this->board.getCurrent()->move(0, y);
            this->board.store(this->score, this->next.pop(), this->trigger);

            this->trigger = Tetris::TriggerType::HARD_DROP;
        }

        if (event == ftxui::Event::Character('z') || event == ftxui::Event::Character('Z'))
        {
            Tetris::Tetromino tetromino;

            if (this->hold.hasHold())
            {
                tetromino = this->hold.getHold();
            }
            else
            {
                tetromino = this->next.pop();
            }

            this->hold.setHold(*this->board.getCurrent());

            this->board.setCurrent(tetromino);

            this->trigger = Tetris::TriggerType::SWAP_HOLD;
            return true;
        };

        this->trigger = Tetris::TriggerType::NO_TRIGGER;

        return false;
    }

    ftxui::Element getDebugElement()
    {
        std::string trigger;

        switch (this->trigger)
        {
        case MOVE_LEFT:
            trigger = "Move Left";
            break;
        case MOVE_RIGHT:
            trigger = "Move Right";
            break;
        case SOFT_DROP:
            trigger = "Soft Drop";
            break;
        case HARD_DROP:
            trigger = "Hard Drop";
            break;
        case ROTATE_LEFT:
            trigger = "Rotate Left";
            break;
        case ROTATE_RIGHT:
            trigger = "Rotate Right";
            break;
        case SWAP_HOLD:
            trigger = "Swap Hold";
            break;
        case NO_TRIGGER:
            trigger = "<NULL>";
            break;
        }

        return ftxui::window(
            ftxui::text("Debug"),
            ftxui::vbox({
                Tetris::OutputHelper::getKeyValueText("Easy Mode", this->isEasyMode),
                Tetris::OutputHelper::getKeyValueText("Last Input", this->lastInput),
                Tetris::OutputHelper::getKeyValueText("Event Trigger", trigger),
            })
        );
    }

    ftxui::Component getRenderer(bool debug = false)
    {
        return ftxui::Renderer([debug, this] {
            std::vector<ftxui::Element> elements;

            elements.push_back(this->board.getBoardElement(this->isEasyMode));

            elements.push_back(ftxui::vbox(
                {this->next.getElement(),
                 this->score.getElement(),
                 ftxui::canvas(Tetris::Canvas::createCanvas(5, 7)),
                 this->hold.getElement()}
            ));

            if (debug)
            {
                elements.push_back(ftxui::vbox({this->board.getDebugElement(), this->getDebugElement()}));
            }

            return ftxui::hbox(elements);
        });
    }
};
} // namespace Tetris