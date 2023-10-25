#include "t_renderer/t_key_value.hpp"

namespace Tetris::Renderer
{
ftxui::Element KeyValue::create(std::string key, std::string value)
{
    return ftxui::hbox({ftxui::text(key + ": "), ftxui::text(value) | ftxui::color(Tetris::Renderer::Color::valueColor)}
    );
}

ftxui::Element KeyValue::create(std::string key, int value)
{
    return Tetris::Renderer::KeyValue::create(key, std::to_string(value));
}

ftxui::Element KeyValue::create(std::string key, double value)
{
    std::stringstream stream;
    stream << std::fixed << std::setprecision(3) << value;

    return Tetris::Renderer::KeyValue::create(key, stream.str());
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
            | ftxui::color(value ? Tetris::Renderer::Color::trueColor : Tetris::Renderer::Color::falseColor),
    });
}
} // namespace Tetris::Renderer