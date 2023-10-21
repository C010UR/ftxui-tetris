#pragma once

#include "ftxui/dom/elements.hpp"
#include "ftxui/dom/node.hpp"
#include "output_helper.hpp"
#include <cstdio>
#include <stdio.h>
#include <string>
#include <utility>
#include <vector>
namespace Tetris
{
enum ScoreType
{
    SCORE_SINGLE,
    SCORE_DOUBLE,
    SCORE_TRIPLE,
    SCORE_TETRIS,
    SCORE_MINI_T_SPIN_NO_LINES,
    SCORE_T_SPIN_NO_LINES,
    SCORE_MINI_T_SPIN_SINGLE,
    SCORE_T_SPIN_SINGLE,
    SCORE_MINI_T_SPIN_DOUBLE,
    SCORE_T_SPIN_DOUBLE,
    SCORE_T_SPIN_TRIPLE,
    SCORE_SOFT_DROP,
    SCORE_HARD_DROP,
    SCORE_SINGLE_LINE_PERFECT_CLEAR,
    SCORE_DOUBLE_LINE_PERFECT_CLEAR,
    SCORE_TRIPLE_LINE_PERFECT_CLEAR,
    SCORE_TETRIS_LINE_PERFECT_CLEAR,
};

class Score
{
  private:
    int score;
    int level;
    int linesCleared;

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

    void add(Tetris::ScoreType scoreType, int level = 1)
    {
        switch (scoreType)
        {
        case SCORE_SINGLE:
            this->score += 100 * level;
            break;
        case SCORE_DOUBLE:
            this->score += 300 * level;
            break;
        case SCORE_TRIPLE:
            this->score += 500 * level;
            break;
        case SCORE_TETRIS:
            this->score += 800 * level;
            break;
        case SCORE_MINI_T_SPIN_NO_LINES:
            this->score += 100 * level;
            break;
        case SCORE_T_SPIN_NO_LINES:
            this->score += 400 * level;
            break;
        case SCORE_MINI_T_SPIN_SINGLE:
            this->score += 200 * level;
            break;
        case SCORE_T_SPIN_SINGLE:
            this->score += 800 * level;
            break;
        case SCORE_MINI_T_SPIN_DOUBLE:
            this->score += 400 * level;
            break;
        case SCORE_T_SPIN_DOUBLE:
            this->score += 1200 * level;
            break;
        case SCORE_T_SPIN_TRIPLE:
            this->score += 1600 * level;
            break;
        case SCORE_SOFT_DROP:
            this->score += 1;
            break;
        case SCORE_HARD_DROP:
            this->score += 2;
            break;
        case SCORE_SINGLE_LINE_PERFECT_CLEAR:
            this->score += 800 * level;
            break;
        case SCORE_DOUBLE_LINE_PERFECT_CLEAR:
            this->score += 1200 * level;
            break;
        case SCORE_TRIPLE_LINE_PERFECT_CLEAR:
            this->score += 1800 * level;
            break;
        case SCORE_TETRIS_LINE_PERFECT_CLEAR:
            this->score += 2000 * level;
            break;
        }
    }

  public:
    Score(int level = 1)
    {
        this->score        = 0;
        this->level        = level;
        this->linesCleared = 0;
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

    void update(int linesCleared)
    {

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
                Tetris::OutputHelper::getKeyValueText("Score", this->score),
                Tetris::OutputHelper::getKeyValueText("Level", this->level),
            })
        );
    }
};
} // namespace Tetris