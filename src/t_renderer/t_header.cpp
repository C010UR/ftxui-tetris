#include "t_renderer/t_header.hpp"

namespace Tetris::Renderer
{
ftxui::Element Header::tetris()
{
    return ftxui::vbox({
               ftxui::text("████████╗███████╗████████╗██████╗ ██╗███████╗"),
               ftxui::text("╚══██╔══╝██╔════╝╚══██╔══╝██╔══██╗██║██╔════╝"),
               ftxui::text("   ██║   █████╗     ██║   ██████╔╝██║███████╗"),
               ftxui::text("   ██║   ██╔══╝     ██║   ██╔══██╗██║╚════██║"),
               ftxui::text("   ██║   ███████╗   ██║   ██║  ██║██║███████║"),
               ftxui::text("   ╚═╝   ╚══════╝   ╚═╝   ╚═╝  ╚═╝╚═╝╚══════╝"),
           })
           | ftxui::color(CurrentTheme::mainGradient());
}

ftxui::Element Header::gameOver()
{
    return ftxui::vbox({
               ftxui::text(" ██████╗  █████╗ ███╗   ███╗███████╗     ██████╗ ██╗   ██╗███████╗██████╗ "),
               ftxui::text("██╔════╝ ██╔══██╗████╗ ████║██╔════╝    ██╔═══██╗██║   ██║██╔════╝██╔══██╗"),
               ftxui::text("██║  ███╗███████║██╔████╔██║█████╗      ██║   ██║██║   ██║█████╗  ██████╔╝"),
               ftxui::text("██║   ██║██╔══██║██║╚██╔╝██║██╔══╝      ██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗"),
               ftxui::text("╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗    ╚██████╔╝ ╚████╔╝ ███████╗██║  ██║"),
               ftxui::text(" ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝     ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝"),
           })
           | ftxui::color(CurrentTheme::badGradient());
}

ftxui::Element Header::options()
{
    return ftxui::vbox({
               ftxui::text(" ██████╗ ██████╗ ████████╗██╗ ██████╗ ███╗   ██╗███████╗"),
               ftxui::text("██╔═══██╗██╔══██╗╚══██╔══╝██║██╔═══██╗████╗  ██║██╔════╝"),
               ftxui::text("██║   ██║██████╔╝   ██║   ██║██║   ██║██╔██╗ ██║███████╗"),
               ftxui::text("██║   ██║██╔═══╝    ██║   ██║██║   ██║██║╚██╗██║╚════██║"),
               ftxui::text("╚██████╔╝██║        ██║   ██║╚██████╔╝██║ ╚████║███████║"),
               ftxui::text(" ╚═════╝ ╚═╝        ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝"),
           })
           | ftxui::color(CurrentTheme::mainGradient());
}

ftxui::Element Header::controls()
{
    return ftxui::vbox({
               ftxui::text(" ██████╗ ██████╗ ███╗   ██╗████████╗██████╗  ██████╗ ██╗     ███████╗"),
               ftxui::text("██╔════╝██╔═══██╗████╗  ██║╚══██╔══╝██╔══██╗██╔═══██╗██║     ██╔════╝"),
               ftxui::text("██║     ██║   ██║██╔██╗ ██║   ██║   ██████╔╝██║   ██║██║     ███████╗"),
               ftxui::text("██║     ██║   ██║██║╚██╗██║   ██║   ██╔══██╗██║   ██║██║     ╚════██║"),
               ftxui::text("╚██████╗╚██████╔╝██║ ╚████║   ██║   ██║  ██║╚██████╔╝███████╗███████║"),
               ftxui::text(" ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝   ╚═╝   ╚═╝  ╚═╝ ╚═════╝ ╚══════╝╚══════╝"),
           })
           | ftxui::color(CurrentTheme::mainGradient());
}

ftxui::Element Header::number(int value)
{
    int height = 6;
    // clang-format off
    const std::vector<std::vector<std::string>> numbers = {
        {
            " ██████╗ ",
            "██╔═████╗",
            "██║██╔██║",
            "████╔╝██║",
            "╚██████╔╝",
            " ╚═════╝ "
        }, {
            " ██╗ ",
            "███║ ",
            "╚██║ ",
            " ██║ ",
            " ██║ ",
            " ╚═╝ "
        }, {
            "██████╗  ",
            "╚════██╗ ",
            " █████╔╝ ",
            "██╔═══╝  ",
            "███████╗ ",
            "╚══════╝ "
        }, {
            "██████╗  ",
            "╚════██╗ ",
            " █████╔╝ ",
            " ╚═══██╗ ",
            "██████╔╝ ",
            "╚═════╝  "
        }, {
            "██╗  ██╗ ",
            "██║  ██║ ",
            "███████║ ",
            "╚════██║ ",
            "     ██║ ",
            "     ╚═╝ "
        }, {
            "███████╗ ",
            "██╔════╝ ",
            "███████╗ ",
            "╚════██║ ",
            "███████║ ",
            "╚══════╝ "
        }, {
            " ██████╗ ",
            "██╔════╝ ",
            "███████╗ ",
            "██╔═══██╗",
            "╚██████╔╝",
            " ╚═════╝ "
        }, {
            "███████╗ ",
            "╚════██║ ",
            "    ██╔╝ ",
            "   ██╔╝  ",
            "   ██║   ",
            "   ╚═╝   "
        }, {
            " █████╗  ",
            "██╔══██╗ ",
            "╚█████╔╝ ",
            "██╔══██╗ ",
            "╚█████╔╝ ",
            " ╚════╝  "
        }, {
            " █████╗  ",
            "██╔══██╗ ",
            "╚██████║ ",
            " ╚═══██║ ",
            " █████╔╝ ",
            " ╚════╝  "
        }
    };
    // clang-format on

    std::vector<std::string> lines(height, "");
    std::vector<int>         digits;

    if (value == 0)
    {
        digits.push_back(0);
    }
    else
    {
        while (value != 0)
        {
            digits.push_back(value % 10);
            value /= 10;
        }
    }

    for (int i = (int)digits.size() - 1; i >= 0; i--)
    {
        for (int j = 0; j < height; j++)
        {
            lines[j] += numbers[digits[i]][j];
        }
    }

    ftxui::Elements elements;

    for (int i = 0; i < height; i++)
    {
        elements.push_back(ftxui::text(lines[i]));
    }

    return ftxui::vbox(elements) | ftxui::color(CurrentTheme::badGradient());
}
} // namespace Tetris::Renderer