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
    SINGLE,
    DOUBLE,
    TRIPLE,
    TETRIS,
    MINI_T_SPIN_NO_LINES,
    T_SPIN_NO_LINES,
    MINI_T_SPIN_SINGLE,
    T_SPIN_SINGLE,
    MINI_T_SPIN_DOUBLE,
    T_SPIN_DOUBLE,
    T_SPIN_TRIPLE,
    SOFT_DROP,
    HARD_DROP,
    SINGLE_LINE_PERFECT_CLEAR,
    DOUBLE_LINE_PERFECT_CLEAR,
    TRIPLE_LINE_PERFECT_CLEAR,
    TETRIS_LINE_PERFECT_CLEAR,
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
        case SINGLE:
            this->score += 100 * level;
            break;
        case DOUBLE:
            this->score += 300 * level;
            break;
        case TRIPLE:
            this->score += 500 * level;
            break;
        case TETRIS:
            this->score += 800 * level;
            break;
        case MINI_T_SPIN_NO_LINES:
            this->score += 100 * level;
            break;
        case T_SPIN_NO_LINES:
            this->score += 400 * level;
            break;
        case MINI_T_SPIN_SINGLE:
            this->score += 200 * level;
            break;
        case T_SPIN_SINGLE:
            this->score += 800 * level;
            break;
        case MINI_T_SPIN_DOUBLE:
            this->score += 400 * level;
            break;
        case T_SPIN_DOUBLE:
            this->score += 1200 * level;
            break;
        case T_SPIN_TRIPLE:
            this->score += 1600 * level;
            break;
        case SOFT_DROP:
            this->score += 1;
            break;
        case HARD_DROP:
            this->score += 2;
            break;
        case SINGLE_LINE_PERFECT_CLEAR:
            this->score += 800 * level;
            break;
        case DOUBLE_LINE_PERFECT_CLEAR:
            this->score += 1200 * level;
            break;
        case TRIPLE_LINE_PERFECT_CLEAR:
            this->score += 1800 * level;
            break;
        case TETRIS_LINE_PERFECT_CLEAR:
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