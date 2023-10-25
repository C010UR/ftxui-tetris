#include "t_renderer/t_data_transformer.hpp"

namespace Tetris::Renderer
{
std::string DataTransformer::transformKey(std::string key)
{
    if (key == "\x1B[D")
    {
        return "←";
    }
    if (key == "\x1B[C")
    {
        return "→";
    }
    if (key == "\x1B[A")
    {
        return "↑";
    }
    if (key == "\x1B[B")
    {
        return "↓";
    }
    if (key == "\x1B[1;5D")
    {
        return "Ctrl + ←";
    }
    if (key == "\x1B[1;5C")
    {
        return "Ctrl + →";
    }
    if (key == "\x1B[1;5A")
    {
        return "Ctrl + ↑";
    }
    if (key == "\x1B[1;5B")
    {
        return "Ctrl + ↓";
    }
    if (key == std::string({127}))
    {
        return "Backspace";
    }
    if (key == "\x1B[3~")
    {
        return "Delete";
    }
    if (key == "\x1B")
    {
        return "Escape";
    }
    if (key == std::string({10}))
    {
        return "Return";
    }
    if (key == std::string({9}))
    {
        return "Tab";
    }
    if (key == std::string({27, 91, 90}))
    {
        return "Shift + Tab";
    }

    if (key == "\x1BOP")
    {
        return "F1";
    }
    if (key == "\x1BOQ")
    {
        return "F2";
    }
    if (key == "\x1BOR")
    {
        return "F3";
    }
    if (key == "\x1BOS")
    {
        return "F4";
    }
    if (key == "\x1B[15~")
    {
        return "F5";
    }
    if (key == "\x1B[17~")
    {
        return "F6";
    }
    if (key == "\x1B[18~")
    {
        return "F7";
    }
    if (key == "\x1B[19~")
    {
        return "F8";
    }
    if (key == "\x1B[20~")
    {
        return "F9";
    }
    if (key == "\x1B[21~")
    {
        return "F10";
    }
    if (key == "\x1B[23~")
    {
        return "F11";
    }
    if (key == "\x1B[24~")
    {
        return "F12";
    }

    if (key == std::string({27, 91, 72}))
    {
        return "Home";
    }
    if (key == std::string({27, 91, 70}))
    {
        return "End";
    }
    if (key == std::string({27, 91, 53, 126}))
    {
        return "PageUp";
    }
    if (key == std::string({27, 91, 54, 126}))
    {
        return "PageDown";
    }

    return key;
}
} // namespace Tetris::Renderer