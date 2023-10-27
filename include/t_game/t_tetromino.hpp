#pragma once

#include "ftxui/screen/color.hpp"
#include "t_game/t_enums.hpp"
#include "t_game/t_point.hpp"

#include <charconv>
#include <stdexcept>
#include <string>
#include <vector>

namespace Tetris::Game
{
class Tetromino
{
  private:

    tetromino_rotations_t                         tetromino;
    std::vector<std::vector<Tetris::Game::Point>> wallKickOffsets;
    int                                           rotate(Tetris::Game::RotationType rotation);

  public:

    Tetris::Game::Point currentPosition;

    Tetris::Game::TetrominoType type;
    ftxui::Color                color;

    std::vector<Tetris::Game::Point> testPoints;

    int  currentRotation;
    bool isLastMoveResultedInSpin;
    bool isMiniSpin;

    Tetromino(){};

    Tetromino(
        tetromino_rotations_t                         tetromino,
        std::vector<std::vector<Tetris::Game::Point>> wallKickOffsets,
        ftxui::Color                                  color,
        Tetris::Game::TetrominoType                   type
    );

    static tetromino_rotations_t parseInputTetromino(std::vector<std::vector<std::string>> data, int size);

    std::vector<Tetris::Game::Point> getWallKickTestData(Tetris::Game::RotationType rotation);

    bool   canMove(const board_t &board, Tetris::Game::Point offset);
    bool   canRotate(const board_t &board, Tetris::Game::Point &offset, Tetris::Game::RotationType rotation);
    bool   isColliding(const board_t &board);
    double getRowsToObstacle(const board_t &board);

    void move(
        const board_t &board, Tetris::Game::Point offset, Tetris::Game::RotationType = Tetris::Game::RotationType::NONE
    );
    void reset();
    void reset(int width);

    void                   resetSpinData();
    Tetris::Game::SpinType getSpinType();

    tetromino_t getData();
    tetromino_t getData(int rotation);
};
} // namespace Tetris::Game