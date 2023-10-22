#pragma once

#include <algorithm>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>
#include <mutex>
#include <utility>
#include <vector>

#include "board.hpp"
#include "canvas.hpp"
#include "config.hpp"
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
    Tetris::Board  board;
    Tetris::Score  score;
    Tetris::Next   next;
    Tetris::Hold   hold;
    Tetris::Config config;

    int storeDelay;
    int softDropDelay;
    int comboDelay;

    bool              isSoftDrop;
    Tetris::TSpinType TSpin;

    std::vector<Tetris::TriggerType> triggers;

    int getTicksInMs(double ms)
    {
        return ms / 1000 * this->config.updatesPerSecond;
    }

    double getGravityPerUpdate()
    {
        return std::min(
            (1000 / (isSoftDrop ? std::min(50., this->score.getGravity()) : this->score.getGravity()))
                / this->config.updatesPerSecond,
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

        if (this->isSoftDrop)
        {
            this->score.add(Tetris::ScoreType::SOFT_DROP);
        }
    }

    void handleDropDelay()
    {
        if (this->storeDelay != this->getTicksInMs(this->config.storeDelay))
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

        if (linesCleared > 0)
        {
            this->comboDelay = this->getTicksInMs(this->config.comboDelay);
            this->score.update(linesCleared, this->board.isBoardClear(), this->TSpin);
        }

        this->hold.unblock();
    }

    void handleSoftDrop()
    {
        if (!this->isSoftDrop)
        {
            return;
        }

        this->softDropDelay++;

        if (this->softDropDelay == this->getTicksInMs(this->config.softDropDelay))
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

    void handleCombo()
    {
        if (this->comboDelay > 0)
        {
            this->comboDelay--;
        }

        if (this->comboDelay == 0)
        {
            this->score.resetCombo();
        }
    }

  public:
    Game(Tetris::Config config)
    {
        this->score  = Tetris::Score();
        this->next   = Tetris::Next();
        this->hold   = Tetris::Hold();
        this->board  = Tetris::Board(this->next.pop());
        this->config = config;

        this->softDropDelay = 0;
        this->storeDelay    = 0;
        this->comboDelay    = 0;
        this->isSoftDrop    = false;
        this->TSpin         = Tetris::TSpinType::T_SPIN_NONE;
    }

    void update()
    {
        this->handleSoftDrop();
        this->handleGravity();
        this->handleDropDelay();
        this->handleCombo();
    }

    void handleTriggers()
    {
        this->TSpin = Tetris::TSpinType::T_SPIN_NONE;

        for (int i = 0; i < (int)this->triggers.size(); i++)
        {
            int x = 0, y = 0; // used by rotate

            switch (triggers[i])
            {
            case Tetris::TriggerType::MOVE_LEFT:
                if (this->board.canMove(-1, 0))
                {
                    this->board.getCurrent()->move(-1, 0);
                }

                break;
            case Tetris::TriggerType::MOVE_RIGHT:
                if (this->board.canMove(1, 0))
                {
                    this->board.getCurrent()->move(1, 0);
                }

                break;
            case Tetris::TriggerType::SOFT_DROP:
                this->isSoftDrop    = true;
                this->softDropDelay = 0;
                break;
            case Tetris::TriggerType::HARD_DROP:
                this->score.add(Tetris::ScoreType::HARD_DROP, this->board.getHardDropY());
                this->board.getCurrent()->move(0, this->board.getHardDropY());
                this->handleStore();
                break;
            case Tetris::TriggerType::ROTATE_LEFT:
                if (this->board.canRotate(x, y, Tetris::RotationType::LEFT))
                {
                    this->board.getCurrent()->move(x, y, Tetris::RotationType::LEFT);
                }

                break;
            case Tetris::TriggerType::ROTATE_RIGHT:
                if (this->board.canRotate(x, y, Tetris::RotationType::RIGHT))
                {
                    this->board.getCurrent()->move(x, y, Tetris::RotationType::RIGHT);
                }

                break;
            case Tetris::TriggerType::SWAP_HOLD:
                this->handleSwapHold();
                break;
            case Tetris::TriggerType::FORFEIT:
                this->board.setGameOver(true);
                break;
            case Tetris::TriggerType::NO_TRIGGER:
                break;
            }
        }

        this->triggers.clear();
    }

    bool handleEvent(ftxui::Event event)
    {
        Tetris::TriggerType trigger = this->config.handleEvent(event);

        if (trigger != Tetris::TriggerType::NO_TRIGGER)
        {
            this->triggers.push_back(trigger);
        }

        return false;
    }

    ftxui::Element getDebugElement()
    {
        return ftxui::window(
            ftxui::text("Debug"),
            ftxui::vbox({
                Tetris::OutputHelper::getKeyValueText("Easy Mode", this->config.isEasyMode),
                Tetris::OutputHelper::getKeyValueText("Store delay", this->storeDelay * this->config.updatesPerSecond),
                Tetris::OutputHelper::getKeyValueText("Game Over", this->board.isGameOver()),
                Tetris::OutputHelper::getKeyValueText("Hold Blocked", this->hold.isBlocked()),
                Tetris::OutputHelper::getKeyValueText("Updates per second", this->config.updatesPerSecond),
                Tetris::OutputHelper::getKeyValueText("Gravity", this->score.getGravity()),
                Tetris::OutputHelper::getKeyValueText("Gravity per Update", this->getGravityPerUpdate()),
                Tetris::OutputHelper::getKeyValueText(
                    "Soft drop delay", this->softDropDelay * this->config.updatesPerSecond
                ),
                Tetris::OutputHelper::getKeyValueText("Soft drop", this->isSoftDrop),
                Tetris::OutputHelper::getKeyValueText("Combo delay", this->comboDelay * this->config.updatesPerSecond),
                Tetris::OutputHelper::getKeyValueText("T-Spin Type", Tetris::OutputHelper::enumToString(this->TSpin)),
            })
        );
    }

    ftxui::Component getRenderer()
    {
        return ftxui::Renderer([this] {
            std::vector<ftxui::Element> elements;

            elements.push_back(
                ftxui::vbox(
                    {this->score.getElement(),
                     ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 14),
                     this->score.getComboElement()}
                )
                | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 20)
            );

            elements.push_back(this->board.getBoardElement(this->config.isEasyMode));

            elements.push_back(this->score.getComboTimeElement(
                this->comboDelay, this->getTicksInMs(this->config.comboDelay), this->board.height
            ));

            elements.push_back(ftxui::vbox(
                {this->next.getElement(),
                 ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 10),
                 this->hold.getElement()}
            ));

            if (this->config.isDebug)
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