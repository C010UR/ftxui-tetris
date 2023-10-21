#pragma once

#include <algorithm>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
#include <mutex>
#include <utility>
#include <vector>

#include "board.hpp"
#include "canvas.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/screen/color.hpp"
#include "ftxui/screen/screen.hpp"
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

    double updatesPerSecond;

    int  storeDelay;
    int  softDropDelay;
    bool isSoftDrop;

    std::vector<Tetris::TriggerType> triggers;

    int getTicksInMs(double ms)
    {
        return ms / 1000 * updatesPerSecond;
    }

    double getGravityPerUpdate()
    {
        return std::min(
            (1000 / (isSoftDrop ? std::min(50., this->score.getGravity()) : this->score.getGravity()))
                / this->updatesPerSecond,
            (double)std::max(this->board.getHardDropY(), 1)
        );
    }

    void handleGravity()
    {
        this->storeDelay++;
        double offset = this->getGravityPerUpdate();

        if (!this->board.canMove(0, offset))
        {
            return;
        }

        this->board.getCurrent()->move(0, offset);
        this->storeDelay = 0;
    }

    void handleDropDelay()
    {
        if (this->storeDelay != this->getTicksInMs(500))
        {
            return;
        }

        this->handleStore();
        this->storeDelay = 0;
    }

    void handleStore()
    {
        if (this->board.canMove(0, 1))
        {
            return;
        }

        int linesCleared = this->board.store(this->next.pop());
        this->score.update(linesCleared);
        this->hold.unblock();
    }

    void handleSoftDrop()
    {
        if (!this->isSoftDrop)
        {
            return;
        }

        this->softDropDelay++;

        if (this->softDropDelay == this->getTicksInMs(50))
        {
            this->isSoftDrop    = false;
            this->softDropDelay = 0;
        }
    }

    void handleSwapHold()
    {
        Tetris::Tetromino tetromino = this->hold.hasHold() ? this->hold.getHold() : this->next.pop();

        this->hold.setHold(*this->board.getCurrent());
        this->board.setCurrent(tetromino);
        this->hold.block();
    }

  public:
    Game(double updatesPerSecond, bool isEasyMode = false)
    {
        this->isEasyMode = isEasyMode;

        this->score            = Tetris::Score();
        this->next             = Tetris::Next();
        this->hold             = Tetris::Hold();
        this->board            = Tetris::Board(this->next.pop());
        this->updatesPerSecond = updatesPerSecond;
        this->softDropDelay    = 0;
        this->storeDelay       = 0;
        this->isSoftDrop       = false;
    }

    void update()
    {
        this->handleSoftDrop();
        this->handleGravity();
        this->handleDropDelay();
    }

    void handleTriggers()
    {
        for (int i = 0; i < (int)this->triggers.size(); i++)
        {
            int x = 0, y = 0; // used by rotate

            switch (triggers[i])
            {
            case MOVE_LEFT:
                if (this->board.canMove(-1, 0))
                {
                    this->board.getCurrent()->move(-1, 0);
                }

                break;
            case MOVE_RIGHT:
                if (this->board.canMove(1, 0))
                {
                    this->board.getCurrent()->move(1, 0);
                }

                break;
            case SOFT_DROP:
                this->isSoftDrop    = true;
                this->softDropDelay = 0;
                break;
            case HARD_DROP:
                this->board.getCurrent()->move(0, this->board.getHardDropY());
                this->handleStore();
                break;
            case ROTATE_LEFT:
                if (this->board.canRotate(x, y, Tetris::RotationType::LEFT))
                {
                    this->board.getCurrent()->move(x, y, Tetris::RotationType::LEFT);
                }

                break;
            case ROTATE_RIGHT:
                if (this->board.canRotate(x, y, Tetris::RotationType::RIGHT))
                {
                    this->board.getCurrent()->move(x, y, Tetris::RotationType::RIGHT);
                }

                break;
            case SWAP_HOLD:
                this->handleSwapHold();
                break;
            case NO_TRIGGER:
                break;
            }
        }

        this->triggers.clear();
    }

    bool handleEvent(ftxui::Event event)
    {
        if (event == ftxui::Event::Character('d') || event == ftxui::Event::Character('D'))
        {
            this->triggers.push_back(Tetris::TriggerType::MOVE_RIGHT);
        }

        if (event == ftxui::Event::Character('a') || event == ftxui::Event::Character('A'))
        {
            this->triggers.push_back(Tetris::TriggerType::MOVE_LEFT);
        }

        if (event == ftxui::Event::Character('s') || event == ftxui::Event::Character('S'))
        {
            this->triggers.push_back(Tetris::TriggerType::SOFT_DROP);
        }

        if (event == ftxui::Event::Character('.') || event == ftxui::Event::Character('>'))
        {
            this->triggers.push_back(Tetris::TriggerType::ROTATE_RIGHT);
        }

        if (event == ftxui::Event::Character(',') || event == ftxui::Event::Character('<'))
        {
            this->triggers.push_back(Tetris::TriggerType::ROTATE_LEFT);
        };

        if (event == ftxui::Event::Character(' '))
        {
            this->triggers.push_back(Tetris::TriggerType::HARD_DROP);
        }

        if (event == ftxui::Event::Character('z') || event == ftxui::Event::Character('Z'))
        {
            this->triggers.push_back(Tetris::TriggerType::SWAP_HOLD);
        }

        return false;
    }

    ftxui::Element getDebugElement()
    {
        return ftxui::window(
            ftxui::text("Debug"),
            ftxui::vbox({
                Tetris::OutputHelper::getKeyValueText("Easy Mode", this->isEasyMode),
                Tetris::OutputHelper::getKeyValueText("Store delay", this->storeDelay * this->updatesPerSecond),
                Tetris::OutputHelper::getKeyValueText("Game Over", this->board.isGameOver()),
                Tetris::OutputHelper::getKeyValueText("Hold Blocked", this->hold.isBlocked()),
                Tetris::OutputHelper::getKeyValueText("Updates per second", updatesPerSecond),
                Tetris::OutputHelper::getKeyValueText("Gravity", this->score.getGravity()),
                Tetris::OutputHelper::getKeyValueText("Gravity per Update", this->getGravityPerUpdate()),
                Tetris::OutputHelper::getKeyValueText("Soft drop delay", this->softDropDelay * this->updatesPerSecond),
                Tetris::OutputHelper::getKeyValueText("Soft drop", this->isSoftDrop),
            })
        );
    }

    ftxui::Component getRenderer(bool debug = false)
    {
        return ftxui::Renderer([debug, this] {
            std::vector<ftxui::Element> elements;

            elements.push_back(ftxui::vbox({this->score.getElement()}) | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 15));

            elements.push_back(this->board.getBoardElement(this->isEasyMode));

            elements.push_back(ftxui::vbox(
                {this->next.getElement(),
                 ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 10),
                 this->hold.getElement()}
            ));

            if (debug)
            {
                elements.push_back(ftxui::filler() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 3));

                elements.push_back(
                    ftxui::vbox({this->board.getDebugElement(this->getGravityPerUpdate(), 1)})
                    | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 30)
                );

                elements.push_back(
                    ftxui::vbox({this->score.getDebugElement(), this->getDebugElement()})
                    | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 30)
                );
            }

            return ftxui::hbox(elements);
        });
    }

    bool isGameOver()
    {
        return this->board.isGameOver();
    }
};
} // namespace Tetris