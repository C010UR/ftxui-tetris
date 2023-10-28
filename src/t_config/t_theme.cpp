#include "t_config/t_theme.hpp"

#include "ftxui/screen/color.hpp"
#include "t_renderer/t_current_theme.hpp"

namespace Tetris::Config
{
void Theme::apply(bool withBackgroundColor)
{
    Tetris::Renderer::CurrentTheme::mainColors     = this->mainColors;
    Tetris::Renderer::CurrentTheme::gameOverColors = this->gameOverColors;

    Tetris::Renderer::CurrentTheme::mainColor       = this->mainColor;
    Tetris::Renderer::CurrentTheme::gameOverColor   = this->gameOverColor;
    Tetris::Renderer::CurrentTheme::backgroundColor = withBackgroundColor ? this->backgroundColor : ftxui::Color::Default;

    Tetris::Renderer::CurrentTheme::valueColor = this->valueColor;
    Tetris::Renderer::CurrentTheme::trueColor  = this->trueColor;
    Tetris::Renderer::CurrentTheme::falseColor = this->falseColor;

    Tetris::Renderer::CurrentTheme::IColor = this->IColor;
    Tetris::Renderer::CurrentTheme::OColor = this->OColor;
    Tetris::Renderer::CurrentTheme::TColor = this->TColor;
    Tetris::Renderer::CurrentTheme::JColor = this->JColor;
    Tetris::Renderer::CurrentTheme::LColor = this->LColor;
    Tetris::Renderer::CurrentTheme::SColor = this->SColor;
    Tetris::Renderer::CurrentTheme::ZColor = this->ZColor;
}

void Theme::setDefault()
{
    this->mainColors
        = {ftxui::Color::RGB(76, 209, 55),
           ftxui::Color::RGB(76, 204, 63),
           ftxui::Color::RGB(76, 199, 71),
           ftxui::Color::RGB(75, 179, 101),
           ftxui::Color::RGB(74, 158, 131)};

    this->gameOverColors
        = {ftxui::Color::RGB(232, 65, 24),
           ftxui::Color::RGB(214, 60, 31),
           ftxui::Color::RGB(196, 55, 37),
           ftxui::Color::RGB(160, 45, 50),
           ftxui::Color::RGB(87, 25, 75)};

    this->mainColor       = ftxui::Color::RGB(74, 158, 131);
    this->gameOverColor   = ftxui::Color::RGB(87, 25, 75);
    this->backgroundColor = ftxui::Color::RGB(0, 0, 0);

    this->valueColor = ftxui::Color::RGB(75, 179, 101);
    this->trueColor  = ftxui::Color::RGB(76, 209, 55);
    this->falseColor = ftxui::Color::RGB(232, 65, 24);

    this->IColor = ftxui::Color::RGB(0, 168, 255);
    this->OColor = ftxui::Color::RGB(251, 197, 49);
    this->TColor = ftxui::Color::RGB(156, 136, 255);
    this->JColor = ftxui::Color::RGB(43, 44, 213);
    this->LColor = ftxui::Color::RGB(242, 131, 37);
    this->SColor = ftxui::Color::RGB(76, 209, 55);
    this->ZColor = ftxui::Color::RGB(232, 65, 24);
}

ftxui::Component Theme::getDebugRenderer()
{
    return ftxui::Renderer([this] {
        std::vector<ftxui::Element> elements;

        elements.push_back(Tetris::Renderer::KeyValue::create("Name", this->name));
        elements.push_back(ftxui::separator());

        for (int i = 0; i < (int)this->mainColors.size(); i++)
        {
            elements.push_back(
                Tetris::Renderer::KeyValue::create("Main Gradient " + std::to_string(i + 1), this->mainColors[i])
            );
        }

        elements.push_back(ftxui::separator());

        for (int i = 0; i < (int)this->gameOverColors.size(); i++)
        {
            elements.push_back(Tetris::Renderer::KeyValue::create(
                "Game Over Gradient " + std::to_string(i + 1), this->gameOverColors[i]
            ));
        }

        elements.push_back(ftxui::separator());

        elements.push_back(Tetris::Renderer::KeyValue::create("Main Color", this->mainColor));
        elements.push_back(Tetris::Renderer::KeyValue::create("Background Color", this->backgroundColor));
        elements.push_back(Tetris::Renderer::KeyValue::create("Game Over Color", this->gameOverColor));
        elements.push_back(Tetris::Renderer::KeyValue::create("Value Color", this->valueColor));
        elements.push_back(Tetris::Renderer::KeyValue::create("True Color", this->trueColor));
        elements.push_back(Tetris::Renderer::KeyValue::create("False Color", this->falseColor));

        elements.push_back(ftxui::separator());

        elements.push_back(Tetris::Renderer::KeyValue::create("I Color", this->IColor));
        elements.push_back(Tetris::Renderer::KeyValue::create("O Color", this->OColor));
        elements.push_back(Tetris::Renderer::KeyValue::create("T Color", this->TColor));
        elements.push_back(Tetris::Renderer::KeyValue::create("J Color", this->JColor));
        elements.push_back(Tetris::Renderer::KeyValue::create("L Color", this->LColor));
        elements.push_back(Tetris::Renderer::KeyValue::create("S Color", this->SColor));
        elements.push_back(Tetris::Renderer::KeyValue::create("Z Color", this->ZColor));

        return ftxui::window(ftxui::text("Current Theme"), ftxui::vbox(elements))
               | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 30);
    });
}
} // namespace Tetris::Config