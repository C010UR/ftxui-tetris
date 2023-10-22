#pragma once

#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
#include <ftxui/screen/color.hpp>
#include <iomanip>
#include <ios>
#include <sstream>
#include <string>
#include <vector>

#include "enums.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/linear_gradient.hpp"
namespace Tetris
{
class OutputHelper
{
  public:
    static ftxui::Element getKeyValueText(std::string key, std::string value)
    {
        return ftxui::hbox({ftxui::text(key + ": "), ftxui::text(value) | ftxui::color(OutputHelper::getValueColor())});
    }

    static ftxui::Element getKeyValueText(std::string key, int value)
    {
        return Tetris::OutputHelper::getKeyValueText(key, std::to_string(value));
    }

    static ftxui::Element getKeyValueText(std::string key, double value)
    {
        std::stringstream stream;
        stream << std::fixed << std::setprecision(3) << value;

        return Tetris::OutputHelper::getKeyValueText(key, stream.str());
    }

    static ftxui::Element getKeyValueText(std::string key, ftxui::Color color)
    {
        return ftxui::hbox({
            ftxui::text(key + ": "),
            ftxui::text("██████") | ftxui::color(color) | ftxui::bgcolor(color),
        });
    }

    static ftxui::Element getKeyValueText(std::string key, bool value)
    {
        return ftxui::hbox({
            ftxui::text(key + ": "),
            ftxui::text(value ? "true" : "false")
                | ftxui::color(value ? OutputHelper::getTrueColor() : OutputHelper::getFalseColor()),
        });
    }

    static std::string enumToString(Tetris::TetrominoType value)
    {
        switch (value)
        {

        case TetrominoType::I:
            return "I";
        case TetrominoType::O:
            return "O";
        case TetrominoType::T:
            return "T";
        case TetrominoType::J:
            return "J";
        case TetrominoType::L:
            return "L";
        case TetrominoType::S:
            return "S";
        case TetrominoType::Z:
            return "Z";
        default:
            return "None";
        }
    }

    static std::string enumToString(Tetris::BlockType value)
    {
        switch (value)
        {
        case BlockType::PVT:
            return "PVT";
        case BlockType::BLK:
            return "BLK";
        default:
            return "NIL";
        }
    }

    static std::string enumToString(Tetris::RotationType value)
    {
        switch (value)
        {
        case RotationType::LEFT:
            return "Left";
        case RotationType::RIGHT:
            return "Right";
        default:
            return "None";
        }
    }

    static std::string enumToString(Tetris::TriggerType value)
    {
        switch (value)
        {

        case TriggerType::MOVE_LEFT:
            return "Move Left";
        case TriggerType::MOVE_RIGHT:
            return "Move Right";
        case TriggerType::SOFT_DROP:
            return "Soft Drop";
        case TriggerType::HARD_DROP:
            return "Hard Drop";
        case TriggerType::ROTATE_LEFT:
            return "Rotate Left";
        case TriggerType::ROTATE_RIGHT:
            return "Rotate Right";
        case TriggerType::SWAP_HOLD:
            return "Swap Hold";
        case TriggerType::FORFEIT:
            return "Forfeit";
        default:
            return "None";
        }
    }

    static std::string enumToString(Tetris::TSpinType value)
    {
        switch (value)
        {
        case TSpinType::T_SPIN_FULL:
            return "T-Spin Full";
        case TSpinType::T_SPIN_MINI:
            return "T-Spin Mini";
        default:
            return "None";
        }
    }

    static std::string enumToString(Tetris::ScoreType value)
    {
        switch (value)
        {

        case ScoreType::SINGLE:
            return "Single";
        case ScoreType::DOUBLE:
            return "Double";
        case ScoreType::TRIPLE:
            return "Triple";
        case ScoreType::TETRIS:
            return "TETRIS";
        case ScoreType::MINI_T_SPIN_NO_LINES:
            return "Mini T-Spin";
        case ScoreType::T_SPIN_NO_LINES:
            return "T-Spin";
        case ScoreType::MINI_T_SPIN_SINGLE:
            return "Mini T-Spin Single";
        case ScoreType::T_SPIN_SINGLE:
            return "T-Spin Single";
        case ScoreType::MINI_T_SPIN_DOUBLE:
            return "Mini T-Spin Double";
        case ScoreType::T_SPIN_DOUBLE:
            return "T-Spin Double";
        case ScoreType::T_SPIN_TRIPLE:
            return "T-Spin Triple";
        case ScoreType::SOFT_DROP:
            return "Soft Drop";
        case ScoreType::HARD_DROP:
            return "Hard Drop";
        case ScoreType::SINGLE_LINE_PERFECT_CLEAR:
            return "Perfect Clear";
        case ScoreType::DOUBLE_LINE_PERFECT_CLEAR:
            return "Perfect Clear Double";
        case ScoreType::TRIPLE_LINE_PERFECT_CLEAR:
            return "Perfect Clear Triple";
        case ScoreType::TETRIS_LINE_PERFECT_CLEAR:
            return "Perfect Clear TETRIS";
        default:
            return "None";
        }
    }

    static void configureScreen(ftxui::ScreenInteractive &screen)
    {
        auto cursor  = ftxui::Screen::Cursor();
        cursor.shape = ftxui::Screen::Cursor::Shape::Hidden;
        screen.SetCursor(cursor);
    }

    static ftxui::Element getGiantTetrisText()
    {
        return ftxui::vbox({
                   ftxui::text("████████╗███████╗████████╗██████╗ ██╗███████╗"),
                   ftxui::text("╚══██╔══╝██╔════╝╚══██╔══╝██╔══██╗██║██╔════╝"),
                   ftxui::text("   ██║   █████╗     ██║   ██████╔╝██║███████╗"),
                   ftxui::text("   ██║   ██╔══╝     ██║   ██╔══██╗██║╚════██║"),
                   ftxui::text("   ██║   ███████╗   ██║   ██║  ██║██║███████║"),
                   ftxui::text("   ╚═╝   ╚══════╝   ╚═╝   ╚═╝  ╚═╝╚═╝╚══════╝"),
               })
               | ftxui::color(Tetris::OutputHelper::getGradient());
    }

    static ftxui::Element getGiantGameOverText()
    {
        return ftxui::vbox({
                   ftxui::text(" ██████╗  █████╗ ███╗   ███╗███████╗     ██████╗ ██╗   ██╗███████╗██████╗ "),
                   ftxui::text("██╔════╝ ██╔══██╗████╗ ████║██╔════╝    ██╔═══██╗██║   ██║██╔════╝██╔══██╗"),
                   ftxui::text("██║  ███╗███████║██╔████╔██║█████╗      ██║   ██║██║   ██║█████╗  ██████╔╝"),
                   ftxui::text("██║   ██║██╔══██║██║╚██╔╝██║██╔══╝      ██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗"),
                   ftxui::text("╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗    ╚██████╔╝ ╚████╔╝ ███████╗██║  ██║"),
                   ftxui::text(" ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝     ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝"),
               })
               | ftxui::color(Tetris::OutputHelper::getRedGradient());
    }

    static ftxui::Element getGiantOptionsText()
    {
        return ftxui::vbox({
                   ftxui::text(" ██████╗ ██████╗ ████████╗██╗ ██████╗ ███╗   ██╗███████╗"),
                   ftxui::text("██╔═══██╗██╔══██╗╚══██╔══╝██║██╔═══██╗████╗  ██║██╔════╝"),
                   ftxui::text("██║   ██║██████╔╝   ██║   ██║██║   ██║██╔██╗ ██║███████╗"),
                   ftxui::text("██║   ██║██╔═══╝    ██║   ██║██║   ██║██║╚██╗██║╚════██║"),
                   ftxui::text("╚██████╔╝██║        ██║   ██║╚██████╔╝██║ ╚████║███████║"),
                   ftxui::text(" ╚═════╝ ╚═╝        ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝"),
               })
               | ftxui::color(Tetris::OutputHelper::getGradient());
    }

    static ftxui::Element getGiantControlsText()
    {
        return ftxui::vbox({
                   ftxui::text(" ██████╗ ██████╗ ███╗   ██╗████████╗██████╗  ██████╗ ██╗     ███████╗"),
                   ftxui::text("██╔════╝██╔═══██╗████╗  ██║╚══██╔══╝██╔══██╗██╔═══██╗██║     ██╔════╝"),
                   ftxui::text("██║     ██║   ██║██╔██╗ ██║   ██║   ██████╔╝██║   ██║██║     ███████╗"),
                   ftxui::text("██║     ██║   ██║██║╚██╗██║   ██║   ██╔══██╗██║   ██║██║     ╚════██║"),
                   ftxui::text("╚██████╗╚██████╔╝██║ ╚████║   ██║   ██║  ██║╚██████╔╝███████╗███████║"),
                   ftxui::text(" ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝   ╚═╝   ╚═╝  ╚═╝ ╚═════╝ ╚══════╝╚══════╝"),
               })
               | ftxui::color(Tetris::OutputHelper::getGradient());
    }

    static ftxui::LinearGradient getGradient(float angle = 0)
    {
        return ftxui::LinearGradient()
            .Angle(angle)
            .Stop(ftxui::Color::RGB(76, 209, 55), 0.0)
            .Stop(ftxui::Color::RGB(76, 204, 63), 0.25)
            .Stop(ftxui::Color::RGB(76, 199, 71), 0.5)
            .Stop(ftxui::Color::RGB(75, 179, 101), 0.75)
            .Stop(ftxui::Color::RGB(74, 158, 131), 1.);
    }

    static ftxui::LinearGradient getRedGradient(float angle = 0)
    {
        return ftxui::LinearGradient()
            .Angle(angle)
            .Stop(ftxui::Color::RGB(232, 65, 24), 0.0)
            .Stop(ftxui::Color::RGB(214, 60, 31), 0.25)
            .Stop(ftxui::Color::RGB(196, 55, 37), 0.5)
            .Stop(ftxui::Color::RGB(160, 45, 50), 0.75)
            .Stop(ftxui::Color::RGB(87, 25, 75), 1.);
    }

    static ftxui::Color getValueColor()
    {
        return ftxui::Color::RGB(74, 158, 131);
    }

    static ftxui::Color getFalseColor()
    {
        return ftxui::Color::RGB(232, 65, 24);
    }

    static ftxui::Color getTrueColor()
    {
        return ftxui::Color::RGB(76, 209, 55);
    }
};
} // namespace Tetris