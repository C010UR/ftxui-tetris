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

    std::vector<std::vector<std::vector<Tetris::Game::BlockType>>> tetromino;
    std::vector<std::vector<Tetris::Game::Point>>                  wallKickOffsets;
    int                                                            rotate(Tetris::Game::RotationType rotation);

    bool testIsLastMoveResultedInSpin;
    bool testIsMiniSpin;

  public:

    Tetris::Game::Point currentPosition;

    Tetris::Game::TetrominoType type;
    ftxui::Color                color;

    int  currentRotation;
    bool isLastMoveResultedInSpin;
    bool isMiniSpin;

    Tetromino(){};

    Tetromino(
        std::vector<std::vector<std::vector<Tetris::Game::BlockType>>> tetromino,
        std::vector<std::vector<Tetris::Game::Point>>                  wallKickOffsets,
        ftxui::Color                                                   color,
        Tetris::Game::TetrominoType                                    type
    );

    static std::vector<std::vector<std::vector<Tetris::Game::BlockType>>> parseInputTetromino(
        std::vector<std::vector<std::string>> data, int size
    );

    std::vector<Tetris::Game::Point> getWallKickTestData(Tetris::Game::RotationType rotation);

    bool canMove(const std::vector<std::vector<Tetris::Game::BoardBlockType>> &board, Tetris::Game::Point offset);
    bool canRotate(
        const std::vector<std::vector<Tetris::Game::BoardBlockType>> &board,
        Tetris::Game::Point                                          &offset,
        Tetris::Game::RotationType                                    rotation,
        bool                                                          isDebug = false
    );
    double getRowsToObstacle(const std::vector<std::vector<Tetris::Game::BoardBlockType>> &board);

    void move(Tetris::Game::Point offset, Tetris::Game::RotationType = Tetris::Game::RotationType::NONE);
    void reset();
    void reset(int width);

    void                   resetSpinData();
    Tetris::Game::SpinType getSpinType();
    Tetris::Game::SpinType getTestSpinType();

    std::vector<std::vector<Tetris::Game::BlockType>> getData();
    std::vector<std::vector<Tetris::Game::BlockType>> getData(int rotation);
};
} // namespace Tetris::Game