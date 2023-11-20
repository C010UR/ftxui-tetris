#include "t_renderer/t_header.hpp"

#include "ftxui/dom/node.hpp"

#include <cctype>


namespace Tetris::Renderer {
ftxui::Element Header::transform(std::string str, bool isGameOver)
{
    std::vector<std::string> lines(Header::height, "");

    for (int i = 0; i < (int)str.size(); i++) {
        for (int j = 0; j < Header::height; j++) {
            if (std::isalpha(str[i])) {
                lines[j] += Header::letters[std::toupper(str[i]) - 'A'][j];
            } else if (std::isdigit(str[i])) {
                lines[j] += Header::numbers[str[i] - '0'][j];
            } else if (std::isspace(str[i])) {
                lines[j] += std::string(3, ' ');
            } else {
                int index = -1;

                switch (str[i]) {
                    case '-':
                        index = 0;
                        break;
                    case '!':
                        index = 1;
                        break;
                    case '?':
                        index = 2;
                        break;
                    case ':':
                        index = 3;
                }

                if (index >= 0) {
                    lines[j] += Header::special[index][j];
                }
            }
        }
    }
    
    ftxui::Elements elements;

    for (int i = 0; i < Header::height; i++) {
        elements.push_back(ftxui::text(lines[i]));
    }

    return ftxui::vbox(elements) | ftxui::color(isGameOver ? CurrentTheme::gameOverGradient() : CurrentTheme::mainGradient());
}

ftxui::Element Header::transform(int value, bool isGameOver)
{
    std::vector<std::string> lines(Header::height, "");
    std::vector<int>         digits;

    if (value == 0) {
        digits.push_back(0);
    } else {
        while (value != 0) {
            digits.push_back(value % 10);
            value /= 10;
        }
    }

    for (int i = (int)digits.size() - 1; i >= 0; i--) {
        for (int j = 0; j < Header::height; j++) {
            lines[j] += Header::numbers[digits[i]][j];
        }
    }

    ftxui::Elements elements;

    for (int i = 0; i < Header::height; i++) {
        elements.push_back(ftxui::text(lines[i]));
    }

    return ftxui::vbox(elements) | ftxui::color(isGameOver ? CurrentTheme::gameOverGradient() : CurrentTheme::mainGradient());
}
} // namespace Tetris::Renderer