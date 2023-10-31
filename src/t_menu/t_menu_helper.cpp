#include "t_menu/t_menu_helper.hpp"

#include "ftxui/dom/elements.hpp"
#include "ftxui/dom/node.hpp"
#include "ftxui/screen/color.hpp"
#include "t_renderer/t_current_theme.hpp"

#include <string>

namespace Tetris::Menu
{

ftxui::Component MenuHelper::getAsciiButton(const std::string &name, std::function<void()> function)
{
    return ftxui::Button(name, function, ftxui::ButtonOption::Ascii());
}

ftxui::Component MenuHelper::getAnimatedButton(const std::string &name, std::function<void()> function, bool isGameOver)
{
    return ftxui::Button(
        name,
        function,
        ftxui::ButtonOption::Animated(
            Tetris::Renderer::CurrentTheme::backgroundColor,
            Tetris::Renderer::CurrentTheme::foregroundColor,
            Tetris::Renderer::CurrentTheme::backgroundColor,
            isGameOver ? Tetris::Renderer::CurrentTheme::gameOverColor : Tetris::Renderer::CurrentTheme::mainColor
        )
    );
}

ftxui::Element MenuHelper::getOptionElement(
    const std::string      &name,
    const std::string      &value,
    const ftxui::Component &addButton,
    const ftxui::Component &subButton,
    const bool              validateAdd,
    const bool              validateSub,
    int                     width,
    int                     leftPad
)
{
    width -= name.size() + 1;

    return ftxui::hbox({
        ftxui::filler() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, leftPad),
        ftxui::text(name + ":"),
        ftxui::filler() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, width > 0 ? width + 1 : 1),
        addButton->Render()
            | ftxui::color(validateSub ? Tetris::Renderer::CurrentTheme::falseColor : ftxui::Color::Default),
        subButton->Render()
            | ftxui::color(validateAdd ? Tetris::Renderer::CurrentTheme::trueColor : ftxui::Color::Default),
        ftxui::text(" ("),
        ftxui::text(value) | ftxui::color(Tetris::Renderer::CurrentTheme::valueColor),
        ftxui::text(")"),
    });
}

ftxui::Element MenuHelper::getOptionElement(
    const std::string                &name,
    const double                      value,
    const ftxui::Component           &addButton,
    const ftxui::Component           &subButton,
    const std::function<bool(double)> validateAdd,
    const std::function<bool(double)> validateSub,
    int                               width,
    int                               leftPad
)
{
    std::stringstream stream;
    stream << std::fixed << std::setprecision(3) << value;

    return MenuHelper::getOptionElement(
        name, stream.str(), addButton, subButton, validateAdd(value), validateSub(value), width, leftPad
    );
}

ftxui::Element MenuHelper::getOptionElement(
    const std::string             &name,
    const int                      value,
    const ftxui::Component        &addButton,
    const ftxui::Component        &subButton,
    const std::function<bool(int)> validateAdd,
    const std::function<bool(int)> validateSub,
    int                            width,
    int                            leftPad
)
{
    return MenuHelper::getOptionElement(
        name, std::to_string(value), addButton, subButton, validateAdd(value), validateSub(value), width, leftPad
    );
}

ftxui::Element MenuHelper::getOptionElement(
    const std::string      &name,
    const std::string      &valueString,
    const ftxui::Component &addButton,
    const ftxui::Component &subButton,
    int                     width,
    int                     leftPad
)
{

    return MenuHelper::getOptionElement(name, valueString, addButton, subButton, true, true, width, leftPad);
}

ftxui::Element MenuHelper::getToggleOptionElement(
    const std::string &name, const bool value, const ftxui::Component &toggleButton, int width, int leftPad
)
{
    width -= name.size() + 1;

    return ftxui::hbox(
        ftxui::filler() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, leftPad),
        ftxui::text(name + ":"),
        ftxui::filler() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, width > 0 ? width + 1 : 1),
        toggleButton->Render(),
        ftxui::text(" ("),
        ftxui::text(value ? "ON" : "OFF")
            | ftxui::color(
                value ? Tetris::Renderer::CurrentTheme::trueColor : Tetris::Renderer::CurrentTheme::falseColor
            ),
        ftxui::text(") ")
    );
}

ftxui::Element MenuHelper::getControlsElement(
    const std::string &name, const std::string &controls, const ftxui::Component &button, int width, int leftPad
)
{
    std::string transformedControl = Tetris::Renderer::DataTransformer::transformKey(controls);
    width -= name.size() + 1;

    return ftxui::hbox(
        {ftxui::filler() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, leftPad),
         ftxui::text(name + ":"),
         ftxui::filler() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, width > 0 ? width + 1 : 1),
         button->Render() | ftxui::color(Tetris::Renderer::CurrentTheme::mainColor),
         ftxui::text(" ("),
         ftxui::text(transformedControl) | ftxui::color(Tetris::Renderer::CurrentTheme::valueColor),
         ftxui::text(")")
        }
    );
}

ftxui::Element MenuHelper::getHeaderElement(const std::string &name)
{
    return ftxui::text(name) | ftxui::color(Tetris::Renderer::CurrentTheme::mainColor);
}

ftxui::Element MenuHelper::getButtonMargin(int height)
{
    return ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, height);
}
} // namespace Tetris::Menu
