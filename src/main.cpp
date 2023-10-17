#include "ftxui/component/event.hpp"
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <iostream>
#include <utility>

int main(void)
{
    using namespace ftxui;

    auto screen = ScreenInteractive::FitComponent();

    const int width  = 11;
    const int height = 21;

    const int stepX = 4;
    const int stepY = 4;

    int x = 0;
    int y = 0;

    auto renderer = Renderer([&] {
        auto c = Canvas(width * stepX, height * stepY);
        c.DrawText(x, y, "II", [](Pixel &p) {
            p.foreground_color = Color::Yellow;
            p.bold             = true;
        });

        return canvas(c);
    });

    auto component = CatchEvent(renderer | border, [&](Event event) {
        if (event == Event::Character('a') && x >= stepX)
        {
            x -= stepX;
        }

        if (event == Event::Character('d') && x < (width - 1) * stepX)
        {
            x += stepX;
        }

        if (event == Event::Character('w') && y >= stepY)
        {
            y -= stepY;
        }

        if (event == Event::Character('s') && y < (height - 1) * stepY)
        {
            y += stepY;
        }

        if (event == Event::Character(' '))
        {
            y = (height - 1) * stepY;
        }

        if (event == Event::Character('q'))
        {
            screen.ExitLoopClosure();
            return true;
        }

        return false;
    });
    
    screen.Loop(component);
}