#include "t_renderer/t_key_value.hpp"

namespace Tetris::Renderer {
std::string KeyValue::roundDouble(double value)
{
    std::stringstream stream;
    stream << std::fixed << std::setprecision(3) << value;

    return stream.str();
}

ftxui::Element KeyValue::create(std::string key, std::string value)
{
    return ftxui::hbox({ftxui::text(key + ": "), ftxui::text(value) | ftxui::color(CurrentTheme::valueColor)});
}

ftxui::Element KeyValue::create(std::string key, int value)
{
    return KeyValue::create(key, std::to_string(value));
}

ftxui::Element KeyValue::create(std::string key, double value)
{
    return KeyValue::create(key, KeyValue::roundDouble(value));
}

ftxui::Element KeyValue::create(std::string key, ftxui::Color color)
{
    return ftxui::hbox({
        ftxui::text(key + ": "),
        ftxui::text("██████") | ftxui::color(color) | ftxui::bgcolor(color),
    });
}

ftxui::Element KeyValue::create(std::string key, bool value)
{
    return ftxui::hbox({
        ftxui::text(key + ": "),
        ftxui::text(value ? "true" : "false")
            | ftxui::color(value ? CurrentTheme::trueColor : CurrentTheme::falseColor),
    });
}

ftxui::Element KeyValue::create(std::string key, Tetris::Game::Point value)
{
    return ftxui::hbox({
        ftxui::text(key + ": ("),
        ftxui::text(KeyValue::roundDouble(value.x)) | ftxui::color(CurrentTheme::valueColor),
        ftxui::text(", "),
        ftxui::text(KeyValue::roundDouble(value.y)) | ftxui::color(CurrentTheme::valueColor),
        ftxui::text(")"),
    });
}
} // namespace Tetris::Renderer