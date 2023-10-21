#pragma once

#include "ftxui/dom/canvas.hpp"
#include <ftxui/screen/color.hpp>
#include <utility>
#include <vector>

namespace Tetris
{
enum TetrominoType
{
    I,
    O,
    T,
    J,
    L,
    S,
    Z
};

enum BlockType
{
    NIL,
    PVT,
    BLK
};

enum RotationType
{
    NO_ROTATE,
    LEFT,
    RIGHT
};

class Tetromino
{
  private:
    std::vector<std::vector<std::vector<Tetris::BlockType>>> position;

    std::vector<std::vector<std::pair<int, int>>> wallKickData;

    int currentRotation;

    double x;
    double y;

    ftxui::Color color;

    Tetris::TetrominoType tetrominoType;

  public:
    Tetromino()
        : position({}), wallKickData({}), currentRotation(0), x(0), y(0), color(ftxui::Color::Default),
          tetrominoType(Tetris::TetrominoType::O){};

    Tetromino(
        std::vector<std::vector<std::vector<Tetris::BlockType>>> position,
        std::vector<std::vector<std::pair<int, int>>>            wallKickData,
        ftxui::Color                                             color,
        Tetris::TetrominoType                                    tetrominoType
    )
    {
        this->wallKickData    = wallKickData;
        this->position        = position;
        this->currentRotation = 0;
        this->color           = color;
        this->tetrominoType   = tetrominoType;

        this->x = 0;
        this->y = 0;
    }

    std::vector<std::pair<int, int>> getRotationData(Tetris::RotationType rotation)
    {
        int nextRotation = 0;

        switch (rotation)
        {
        case NO_ROTATE:
            return {
                {0, 0}
            };
        case LEFT:
            nextRotation = this->rotateLeft(this->currentRotation);
            break;
        case RIGHT:
            nextRotation = this->rotateRight(this->currentRotation);
            break;
        }

        auto first  = this->wallKickData[this->currentRotation];
        auto second = this->wallKickData[nextRotation];

        for (int i = 0; i < (int)first.size(); i++)
        {
            first[i].first -= second[i].first;
            first[i].second -= second[i].second;
        }

        return first;
    }

    int rotateLeft(int current)
    {
        return current == 0 ? (int)this->position.size() - 1 : current - 1;
    }

    int rotateRight(int current)
    {
        return current == (int)this->position.size() - 1 ? 0 : current + 1;
    }

    void rotate(Tetris::RotationType rotation)
    {
        switch (rotation)
        {
        case Tetris::RotationType::LEFT:
            this->currentRotation = this->rotateLeft(this->currentRotation);
            break;
        case Tetris::RotationType::RIGHT:
            this->currentRotation = this->rotateRight(this->currentRotation);
            break;
        default:
            break;
        }
    }

    void reset(int width)
    {
        this->currentRotation = 0;
        auto firstPosition    = this->getMatrix();

        int minX = INT_MAX;
        int maxX = 0;
        int minY = INT_MAX;

        for (int i = 0; i < (int)firstPosition.size(); i++)
        {
            for (int j = 0; j < (int)firstPosition[i].size(); j++)
            {
                if (firstPosition[i][j] != BlockType::NIL && minY > i)
                {
                    minY = i;
                }

                if (firstPosition[i][j] != BlockType::NIL && maxX < j)
                {
                    maxX = j;
                }

                if (firstPosition[i][j] != BlockType::NIL && minX > j)
                {
                    minX = j;
                }
            }
        }

        // could create a better algorithm but meh
        this->x = (int)((width / 2) - 1 - minX - (this->tetrominoType != Tetris::TetrominoType::O ? 1 : 0));
        this->y = -minY;
    }

    void move(double x, double y, Tetris::RotationType rotation = Tetris::RotationType::NO_ROTATE)
    {
        this->x += x;
        this->y += y;

        this->rotate(rotation);
    }

    std::vector<std::vector<Tetris::BlockType>> getMatrix()
    {
        return this->position[this->currentRotation];
    }

    std::vector<std::vector<Tetris::BlockType>> getMatrix(int rotation)
    {
        return this->position[rotation];
    }

    ftxui::Color getColor()
    {
        return this->color;
    }

    int getRotation()
    {
        return this->currentRotation;
    }

    double getX()
    {
        return this->x;
    }

    double getY()
    {
        return this->y;
    }

    void setX(double x)
    {
        this->x = x;
    }

    void setY(double y)
    {
        this->y = y;
    }

    Tetris::TetrominoType getTetrominoType()
    {
        return this->tetrominoType;
    }
};
} // namespace Tetris