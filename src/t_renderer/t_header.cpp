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
           | ftxui::color(Tetris::Renderer::CurrentTheme::mainGradient());
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
           | ftxui::color(Tetris::Renderer::CurrentTheme::badGradient());
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
           | ftxui::color(Tetris::Renderer::CurrentTheme::mainGradient());
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
           | ftxui::color(Tetris::Renderer::CurrentTheme::mainGradient());
}
} // namespace Tetris::Renderer