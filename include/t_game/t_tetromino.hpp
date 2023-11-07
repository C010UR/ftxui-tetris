#pragma once

#include "ftxui/screen/color.hpp"
#include "t_game/t_enums.hpp"
#include "t_game/t_point.hpp"

#include <charconv>
#include <climits>
#include <cmath>
#include <stdexcept>
#include <string>
#include <vector>

namespace Tetris::Game {
class Tetromino
{
  private:
    tetromino_rotations_t           tetromino;
    std::vector<std::vector<Point>> wallKickOffsets;
    int                             rotate(RotationType rotation);

  public:
    Point currentPosition;

    TetrominoType type;
    ftxui::Color  color;

    std::vector<Point> testPoints;

    int  currentRotation;
    bool isLastMoveResultedInSpin;
    bool isMiniSpin;

    Tetromino() {};

    Tetromino(
        tetromino_rotations_t           tetromino,
        std::vector<std::vector<Point>> wallKickOffsets,
        ftxui::Color                    color,
        TetrominoType                   type);

    static tetromino_rotations_t parseInputTetromino(std::vector<std::vector<std::string>> data, int size);

    std::vector<Point> getWallKickTestData(RotationType rotation);

    bool   canMove(const board_t &board, Point offset);
    bool   canRotate(const board_t &board, Point &offset, RotationType rotation);
    bool   isColliding(const board_t &board);
    double getRowsToObstacle(const board_t &board);

    void move(const board_t &board, Point offset, RotationType = RotationType::NONE);
    void reset();
    void reset(int width, int offset);

    void     resetSpinData();
    SpinType getSpinType();

    tetromino_t getData();
    tetromino_t getData(int rotation);
};
} // namespace Tetris::Game