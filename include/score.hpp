#pragma once

#include "ftxui/dom/elements.hpp"
#include "ftxui/dom/node.hpp"
#include <cstdio>
#include <stdio.h>
#include <string>
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

  public:
    Score()
    {
        this->score = 0;
    }

    int getScore()
    {
        return this->score;
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

    ftxui::Element getElement()
    {
        const int width = 11;

        char * score = new char[width];

        std::snprintf(score, width, " %08d ", this->score);

        return ftxui::window(
            ftxui::text("Score"), 
            ftxui::text(std::string(score)));
    }
};
} // namespace Tetris