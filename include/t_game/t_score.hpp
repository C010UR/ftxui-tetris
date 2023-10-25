#pragma once

#include "ftxui/component/component_base.hpp"
#include "ftxui/dom/elements.hpp"
#include "t_game/t_enums.hpp"

namespace Tetris::Game
{
class Score
{
  private:

    void                    calculateLevel();
    Tetris::Game::ScoreType calculateScore(
        int linesCleared, bool isBoardClear, Tetris::Game::SpinType spin = Tetris::Game::SpinType::NONE
    );

  public:

    int score;
    int level;
    int combo;
    int totalLinesCleared;

    Tetris::Game::ScoreType lastScoreType;

    Score(int level = 1);

    void add(Tetris::Game::ScoreType type, int lines = 1);
    void update(int linesCleared, bool isBoardClear = false, Tetris::Game::SpinType spin = Tetris::Game::SpinType::NONE);

    double getGravity();
    
    void resetCombo();

    ftxui::Element getStatsElement();
    ftxui::Element getComboElement();
    ftxui::Element getComboGaugeElement(int height, double progress);
};
} // namespace Tetris::Game