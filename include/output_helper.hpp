#pragma once

#include "ftxui/dom/elements.hpp"
#include "ftxui/dom/node.hpp"
#include "ftxui/screen/color.hpp"
#include <iomanip>
#include <ios>
#include <sstream>
#include <string>
namespace Tetris
{
class OutputHelper
{
  public:
    static ftxui::Element getKeyValueText(std::string key, std::string value)
    {
        return ftxui::hbox({ftxui::text(key + ": "), ftxui::text(value) | ftxui::color(ftxui::Color::Yellow1)});
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
            ftxui::text("██████") | ftxui::color(color),
        });
    }

    static ftxui::Element getKeyValueText(std::string key, bool value)
    {
        return ftxui::hbox({
            ftxui::text(key + ": "),
            ftxui::text(value ? "true" : "false") | ftxui::color(value ? ftxui::Color::Green1 : ftxui::Color::Red1),
        });
    }
};
} // namespace Tetris