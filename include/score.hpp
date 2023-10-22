#pragma once

#include <cstdio>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
#include <stdio.h>
#include <string>
#include <utility>
#include <vector>

#include "enums.hpp"
#include "ftxui/dom/linear_gradient.hpp"
#include "ftxui/screen/color.hpp"
#include "output_helper.hpp"
namespace Tetris
{

class Score
{
  private:
    int score;
    int level;
    int linesCleared;
    int combo;

    Tetris::ScoreType lastScore;

    void calculateLevel()
    {
        int level = 1;

        int j = 3;

        for (int i = j; i <= this->linesCleared; i += j)
        {
            level++;
            j += 2;
        }

        this->level = this->level > level ? this->level : level;
    }

    Tetris::ScoreType calculateScore(
        int linesCleared, bool isBoardClear, Tetris::TSpinType TSpin = Tetris::TSpinType::T_SPIN_NONE
    )
    {
        if (linesCleared == 0 && TSpin == Tetris::TSpinType::T_SPIN_NONE)
        {
            return Tetris::ScoreType::NONE;
        }

        if (isBoardClear)
        {
            switch (linesCleared)
            {
            case 1:
                return Tetris::ScoreType::SINGLE_LINE_PERFECT_CLEAR;
            case 2:
                return Tetris::ScoreType::DOUBLE_LINE_PERFECT_CLEAR;
            case 3:
                return Tetris::ScoreType::TRIPLE_LINE_PERFECT_CLEAR;
            default:
                return Tetris::ScoreType::TETRIS_LINE_PERFECT_CLEAR;
            }
        }

        if (TSpin == Tetris::TSpinType::T_SPIN_MINI)
        {
            switch (linesCleared)
            {
            case 1:
                return Tetris::ScoreType::MINI_T_SPIN_SINGLE;
            case 2:
                return Tetris::ScoreType::MINI_T_SPIN_DOUBLE;
            default:
                return Tetris::ScoreType::MINI_T_SPIN_NO_LINES;
            }
        }

        if (TSpin == Tetris::TSpinType::T_SPIN_FULL)
        {
            switch (linesCleared)
            {
            case 1:
                return Tetris::ScoreType::T_SPIN_SINGLE;
            case 2:
                return Tetris::ScoreType::T_SPIN_DOUBLE;
            case 3:
                return Tetris::ScoreType::T_SPIN_TRIPLE;
            default:
                return Tetris::ScoreType::T_SPIN_NO_LINES;
            }
        }

        switch (linesCleared)
        {
        case 1:
            return Tetris::ScoreType::SINGLE;
        case 2:
            return Tetris::ScoreType::DOUBLE;
        case 3:
            return Tetris::ScoreType::TRIPLE;
        default:
            return Tetris::ScoreType::TETRIS;
        }
    }

  public:
    Score(int level = 1)
    {
        this->score        = 0;
        this->level        = level;
        this->linesCleared = 0;
        this->combo        = 0;
        this->lastScore    = Tetris::ScoreType::NONE;
    }

    void add(Tetris::ScoreType scoreType, int lines = 1)
    {
        if (scoreType == Tetris::ScoreType::SOFT_DROP)
        {
            this->score += 1 * lines;

            return;
        }

        if (scoreType == Tetris::ScoreType::HARD_DROP)
        {
            this->score += 2 * lines;

            return;
        }

        int score = 0;

        switch (scoreType)
        {
        case Tetris::ScoreType::SINGLE:
        case Tetris::ScoreType::MINI_T_SPIN_NO_LINES:
            score = 100;
            break;
        case Tetris::ScoreType::MINI_T_SPIN_SINGLE:
            score = 200;
            break;
        case Tetris::ScoreType::DOUBLE:
            score = 300;
            break;
        case Tetris::ScoreType::T_SPIN_NO_LINES:
        case Tetris::ScoreType::MINI_T_SPIN_DOUBLE:
            score = 400;
            break;
        case Tetris::ScoreType::TRIPLE:
            score = 500;
            break;
        case Tetris::ScoreType::TETRIS:
        case Tetris::ScoreType::SINGLE_LINE_PERFECT_CLEAR:
            score = 800;
            break;
        case Tetris::ScoreType::T_SPIN_SINGLE:
            score = 800;
            break;
        case Tetris::ScoreType::T_SPIN_DOUBLE:
        case Tetris::ScoreType::DOUBLE_LINE_PERFECT_CLEAR:
            score = 1200;
            break;
        case Tetris::ScoreType::T_SPIN_TRIPLE:
            score = 1600;
            break;
        case Tetris::ScoreType::TRIPLE_LINE_PERFECT_CLEAR:
            score = 1800;
            break;
        case Tetris::ScoreType::TETRIS_LINE_PERFECT_CLEAR:
            score = 2000;
            break;
        default:
            score = 0;
            break;
        }

        this->score += (score + 50 * this->combo) * this->level;
        this->lastScore = scoreType;
    }

    int getScore()
    {
        return this->score;
    }

    int getLevel()
    {
        return this->level;
    }

    int getLinesCleared()
    {
        return this->linesCleared;
    }

    void update(int linesCleared, bool isBoardClear = false, Tetris::TSpinType TSpin = Tetris::TSpinType::T_SPIN_NONE)
    {
        if (this->linesCleared > 0)
        {
            this->combo++;
        }

        this->add(this->calculateScore(linesCleared, isBoardClear, TSpin));

        this->linesCleared += linesCleared;
        this->calculateLevel();
    }

    double getGravity()
    {
        const std::vector<double> gravity
            = {1000, 643, 404, 249, 150, 88, 50.5, 28.3, 15.5, 8.27, 4.31, 2.19, 1.08, 0.52, 0.00024};

        if (this->level > (int)gravity.size())
        {
            return gravity[gravity.size() - 1];
        }

        return gravity[level - 1];
    }

    void resetCombo()
    {
        this->combo = 0;
    }

    ftxui::Element getDebugElement()
    {
        return ftxui::vbox({ftxui::window(
            ftxui::text("Level"),
            ftxui::vbox({
                OutputHelper::getKeyValueText("Lines cleared", this->getLinesCleared()),
            })
        )});
    }

    ftxui::Element getElement()
    {
        return ftxui::window(
            ftxui::text("Stats"),
            ftxui::vbox({
                Tetris::OutputHelper::getKeyValueText("Level", this->level),
                Tetris::OutputHelper::getKeyValueText("Score", this->score),
            })
        );
    }

    ftxui::Element getComboTimeElement(int currentTick, int totalTicks, int height)
    {
        return ftxui::gaugeUp(currentTick / (double)totalTicks) | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, height)
               | ftxui::color(OutputHelper::getGradient(90))
               | ftxui::border;
    }

    ftxui::Element getComboElement()
    {
        return ftxui::window(
            ftxui::text("Combo"),
            ftxui::vbox(
                {ftxui::text(Tetris::OutputHelper::enumToString(this->lastScore)),
                 Tetris::OutputHelper::getKeyValueText("Combo", "x" + std::to_string(this->combo))}
            )
        );
    }
};
} // namespace Tetris