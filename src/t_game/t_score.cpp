#include "t_game/t_score.hpp"

#include "t_game/t_enums.hpp"
#include "t_renderer/t_color.hpp"
#include "t_renderer/t_data_transformer.hpp"
#include "t_renderer/t_key_value.hpp"

#include <algorithm>

namespace Tetris::Game
{

void Score::calculateLevel()
{
    int level = 1;

    int j = 3;

    for (int i = j; i <= this->totalLinesCleared; i += j)
    {
        level++;
        j += 2;
    }

    this->level = std::max(this->level, level);
}

Tetris::Game::ScoreType Score::calculateScore(int linesCleared, bool isBoardClear, Tetris::Game::SpinType spin)
{
    {
        if (linesCleared == 0 && spin == Tetris::Game::SpinType::NONE)
        {
            return Tetris::Game::ScoreType::NONE;
        }

        if (isBoardClear)
        {
            switch (linesCleared)
            {
            case 1:
                return Tetris::Game::ScoreType::SINGLE_LINE_PERFECT_CLEAR;
            case 2:
                return Tetris::Game::ScoreType::DOUBLE_LINE_PERFECT_CLEAR;
            case 3:
                return Tetris::Game::ScoreType::TRIPLE_LINE_PERFECT_CLEAR;
            default:
                return Tetris::Game::ScoreType::TETRIS_LINE_PERFECT_CLEAR;
            }
        }

        if (spin == Tetris::Game::SpinType::T_SPIN_MINI)
        {
            switch (linesCleared)
            {
            case 1:
                return Tetris::Game::ScoreType::MINI_T_SPIN_SINGLE;
            case 2:
                return Tetris::Game::ScoreType::MINI_T_SPIN_DOUBLE;
            default:
                return Tetris::Game::ScoreType::MINI_T_SPIN_NO_LINES;
            }
        }

        if (spin == Tetris::Game::SpinType::T_SPIN_FULL)
        {
            switch (linesCleared)
            {
            case 1:
                return Tetris::Game::ScoreType::T_SPIN_SINGLE;
            case 2:
                return Tetris::Game::ScoreType::T_SPIN_DOUBLE;
            case 3:
                return Tetris::Game::ScoreType::T_SPIN_TRIPLE;
            default:
                return Tetris::Game::ScoreType::T_SPIN_NO_LINES;
            }
        }

        switch (linesCleared)
        {
        case 1:
            return Tetris::Game::ScoreType::SINGLE;
        case 2:
            return Tetris::Game::ScoreType::DOUBLE;
        case 3:
            return Tetris::Game::ScoreType::TRIPLE;
        default:
            return Tetris::Game::ScoreType::TETRIS;
        }
    }
}

Score::Score(int level)
{
    this->score             = 0;
    this->level             = level;
    this->totalLinesCleared = 0;
    this->combo             = 0;
    this->lastScoreType     = Tetris::Game::ScoreType::NONE;
}

void Score::add(Tetris::Game::ScoreType type, int lines)
{
    if (type == Tetris::Game::ScoreType::SOFT_DROP)
    {
        this->score += 1 * lines;

        return;
    }

    if (type == Tetris::Game::ScoreType::HARD_DROP)
    {
        this->score += 2 * lines;

        return;
    }

    int score = 0;

    switch (type)
    {
    case Tetris::Game::ScoreType::SINGLE:
    case Tetris::Game::ScoreType::MINI_T_SPIN_NO_LINES:
        score = 100;
        break;
    case Tetris::Game::ScoreType::MINI_T_SPIN_SINGLE:
        score = 200;
        break;
    case Tetris::Game::ScoreType::DOUBLE:
        score = 300;
        break;
    case Tetris::Game::ScoreType::T_SPIN_NO_LINES:
    case Tetris::Game::ScoreType::MINI_T_SPIN_DOUBLE:
        score = 400;
        break;
    case Tetris::Game::ScoreType::TRIPLE:
        score = 500;
        break;
    case Tetris::Game::ScoreType::TETRIS:
    case Tetris::Game::ScoreType::SINGLE_LINE_PERFECT_CLEAR:
        score = 800;
        break;
    case Tetris::Game::ScoreType::T_SPIN_SINGLE:
        score = 800;
        break;
    case Tetris::Game::ScoreType::T_SPIN_DOUBLE:
    case Tetris::Game::ScoreType::DOUBLE_LINE_PERFECT_CLEAR:
        score = 1200;
        break;
    case Tetris::Game::ScoreType::T_SPIN_TRIPLE:
        score = 1600;
        break;
    case Tetris::Game::ScoreType::TRIPLE_LINE_PERFECT_CLEAR:
        score = 1800;
        break;
    case Tetris::Game::ScoreType::TETRIS_LINE_PERFECT_CLEAR:
        score = 2000;
        break;
    default:
        score = 0;
        break;
    }

    this->score += (score + 50 * this->combo) * this->level;
    this->lastScoreType = type;
}

void Score::update(int linesCleared, bool isBoardClear, Tetris::Game::SpinType spin)
{
    if (linesCleared > 0)
    {
        this->combo++;
    }

    this->add(this->calculateScore(linesCleared, isBoardClear, spin));

    this->totalLinesCleared += linesCleared;
    this->calculateLevel();
}

double Score::getGravity()
{
    const std::vector<double> gravity
        = {1000, 643, 404, 249, 150, 88, 50.5, 28.3, 15.5, 8.27, 4.31, 2.19, 1.08, 0.52, 0.00024};

    if (this->level > (int)gravity.size())
    {
        return gravity[gravity.size() - 1];
    }

    return gravity[level - 1];
}

void Score::resetCombo()
{
    this->combo         = 0;
    this->lastScoreType = Tetris::Game::ScoreType::NONE;
}

ftxui::Element Score::getStatsElement()
{
    return ftxui::window(
        ftxui::text("Stats"),
        ftxui::vbox({
            Tetris::Renderer::KeyValue::create("Level", this->level),
            Tetris::Renderer::KeyValue::create("Score", this->score),
            Tetris::Renderer::KeyValue::create("Lines cleared", this->totalLinesCleared),
        })
    );
}

ftxui::Element Score::getComboElement()
{
    return ftxui::window(
        ftxui::text("Combo"),
        ftxui::vbox(
            {ftxui::text(Tetris::Renderer::DataTransformer::toString(this->lastScoreType)),
             Tetris::Renderer::KeyValue::create("Combo", "x" + std::to_string(this->combo))}
        )
    );
}

ftxui::Element Score::getComboGaugeElement(int height, double progress)
{
    return ftxui::gaugeUp(progress) | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, height)
           | ftxui::color(Tetris::Renderer::Color::mainGradient(90)) | ftxui::border;
}


} // namespace Tetris::Game