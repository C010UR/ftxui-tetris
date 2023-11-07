#pragma once

#include "ftxui/dom/canvas.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/dom/node.hpp"
#include "ftxui/screen/color.hpp"
#include "ftxui/screen/screen.hpp"
#include "t_game/t_enums.hpp"
#include "t_game/t_point.hpp"
#include "t_game/t_tetromino.hpp"
#include "t_game/t_tetromino_factory.hpp"
#include "t_renderer/t_canvas.hpp"
#include "t_renderer/t_current_theme.hpp"
#include "t_renderer/t_data_transformer.hpp"
#include "t_renderer/t_key_value.hpp"

#include <vector>

namespace Tetris::Game {
class Board
{
  private:
    std::vector<std::vector<ftxui::Color>> boardColor;
    board_t                                board;

    Tetromino current;

    bool isLineFull(int line);
    int  removeFullLines();

  public:
    inline static const int width  = 10;
    inline static const int actualHeight = 22;
    inline static const int height = 20;

    bool isGameOver;

    Board() {};

    Board(Tetromino tetromino);

    Tetromino *getCurrent();

    void setCurrent(Tetromino tetromino);

    bool   tryRotateCurrent(RotationType rotation);
    bool   canRotateCurrent(RotationType rotation);
    bool   tryMoveCurrent(Point offset);
    bool   canMoveCurrent(Point offset);
    double getRowsToObstacle();

    bool canStore();
    bool isBoardClear();

    int store(Tetromino newTetromino);

    ftxui::Element getDebugElement(double stepX = 1);
    ftxui::Element getElement(bool isEasyMode = false);
};
} // namespace Tetris::Game