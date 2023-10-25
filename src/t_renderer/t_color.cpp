#include "t_renderer/t_color.hpp"

#include "ftxui/screen/color.hpp"

namespace Tetris::Renderer
{
ftxui::LinearGradient Color::mainGradient(float angle)
{
    auto gradient = ftxui::LinearGradient().Angle(angle);

    double position = 0.0;
    double step     = 1. / (mainColors.size() - 1);

    for (auto color : mainColors)
    {
        gradient.Stop(color, position);
        position += step;
    }

    return gradient;
}

ftxui::LinearGradient Color::badGradient(float angle)
{
    auto gradient = ftxui::LinearGradient().Angle(angle);

    double position = 0.0;
    double step     = 1. / (gameOverColors.size() - 1);

    for (auto color : gameOverColors)
    {
        gradient.Stop(color, position);
        position += step;
    }

    return gradient;
}

std::vector<ftxui::Color> Color::mainColors
    = {ftxui::Color::RGB(76, 209, 55),
       ftxui::Color::RGB(76, 204, 63),
       ftxui::Color::RGB(76, 199, 71),
       ftxui::Color::RGB(75, 179, 101),
       ftxui::Color::RGB(74, 158, 131)};

std::vector<ftxui::Color> Color::gameOverColors
    = {ftxui::Color::RGB(232, 65, 24),
       ftxui::Color::RGB(214, 60, 31),
       ftxui::Color::RGB(196, 55, 37),
       ftxui::Color::RGB(160, 45, 50),
       ftxui::Color::RGB(87, 25, 75)};

ftxui::Color Color::mainColor  = ftxui::Color::RGB(74, 158, 131);
ftxui::Color Color::gameOverColor   = ftxui::Color::RGB(87, 25, 75);
ftxui::Color Color::valueColor = ftxui::Color::RGB(75, 179, 101);
ftxui::Color Color::trueColor  = ftxui::Color::RGB(76, 209, 55);
ftxui::Color Color::falseColor = ftxui::Color::RGB(232, 65, 24);

ftxui::Color Color::IColor = ftxui::Color::RGB(0, 168, 255);
ftxui::Color Color::OColor = ftxui::Color::RGB(251, 197, 49);
ftxui::Color Color::TColor = ftxui::Color::RGB(156, 136, 255);
ftxui::Color Color::JColor = ftxui::Color::RGB(43, 44, 213);
ftxui::Color Color::LColor = ftxui::Color::RGB(242, 131, 37);
ftxui::Color Color::SColor = ftxui::Color::RGB(76, 209, 55);
ftxui::Color Color::ZColor = ftxui::Color::RGB(232, 65, 24);
} // namespace Tetris::Renderer