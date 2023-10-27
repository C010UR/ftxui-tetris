#include "t_game/t_score.hpp"

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

ScoreType Score::calculateScore(int linesCleared, bool isBoardClear, SpinType spin)
{
    {
        if (linesCleared == 0 && spin == SpinType::NONE)
        {
            return ScoreType::NONE;
        }

        if (isBoardClear)
        {
            switch (linesCleared)
            {
            case 1:
                return ScoreType::SINGLE_LINE_PERFECT_CLEAR;
            case 2:
                return ScoreType::DOUBLE_LINE_PERFECT_CLEAR;
            case 3:
                return ScoreType::TRIPLE_LINE_PERFECT_CLEAR;
            default:
                return ScoreType::TETRIS_LINE_PERFECT_CLEAR;
            }
        }

        if (spin == SpinType::T_SPIN_MINI)
        {
            switch (linesCleared)
            {
            case 1:
                return ScoreType::MINI_T_SPIN_SINGLE;
            case 2:
                return ScoreType::MINI_T_SPIN_DOUBLE;
            default:
                return ScoreType::MINI_T_SPIN_NO_LINES;
            }
        }

        if (spin == SpinType::T_SPIN_FULL)
        {
            switch (linesCleared)
            {
            case 1:
                return ScoreType::T_SPIN_SINGLE;
            case 2:
                return ScoreType::T_SPIN_DOUBLE;
            case 3:
                return ScoreType::T_SPIN_TRIPLE;
            default:
                return ScoreType::T_SPIN_NO_LINES;
            }
        }

        switch (linesCleared)
        {
        case 1:
            return ScoreType::SINGLE;
        case 2:
            return ScoreType::DOUBLE;
        case 3:
            return ScoreType::TRIPLE;
        default:
            return ScoreType::TETRIS;
        }
    }
}

Score::Score(int level)
{
    this->score             = 0;
    this->level             = level;
    this->totalLinesCleared = 0;
    this->combo             = 0;
    this->lastScoreType     = ScoreType::NONE;
}

void Score::add(ScoreType type, int lines)
{
    if (type == ScoreType::SOFT_DROP)
    {
        this->score += 1 * lines;

        return;
    }

    if (type == ScoreType::HARD_DROP)
    {
        this->score += 2 * lines;

        return;
    }

    int score = 0;

    switch (type)
    {
    case ScoreType::SINGLE:
    case ScoreType::MINI_T_SPIN_NO_LINES:
        score = 100;
        break;
    case ScoreType::MINI_T_SPIN_SINGLE:
        score = 200;
        break;
    case ScoreType::DOUBLE:
        score = 300;
        break;
    case ScoreType::T_SPIN_NO_LINES:
    case ScoreType::MINI_T_SPIN_DOUBLE:
        score = 400;
        break;
    case ScoreType::TRIPLE:
        score = 500;
        break;
    case ScoreType::TETRIS:
    case ScoreType::SINGLE_LINE_PERFECT_CLEAR:
        score = 800;
        break;
    case ScoreType::T_SPIN_SINGLE:
        score = 800;
        break;
    case ScoreType::T_SPIN_DOUBLE:
    case ScoreType::DOUBLE_LINE_PERFECT_CLEAR:
        score = 1200;
        break;
    case ScoreType::T_SPIN_TRIPLE:
        score = 1600;
        break;
    case ScoreType::TRIPLE_LINE_PERFECT_CLEAR:
        score = 1800;
        break;
    case ScoreType::TETRIS_LINE_PERFECT_CLEAR:
        score = 2000;
        break;
    default:
        score = 0;
        break;
    }

    this->score += (score + 50 * this->combo) * this->level;
    this->lastScoreType = type;
}

void Score::update(int linesCleared, bool isBoardClear, SpinType spin)
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
    this->lastScoreType = ScoreType::NONE;
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

ftxui::Element Score::getComboGaugeElement(double progress)
{
    return ftxui::gaugeUp(progress) | ftxui::color(Tetris::Renderer::CurrentTheme::mainGradient(90)) | ftxui::border;
}

} // namespace Tetris::Game