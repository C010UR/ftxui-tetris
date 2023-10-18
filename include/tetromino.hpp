#pragma once

#include "ftxui/dom/canvas.hpp"
#include <ftxui/screen/color.hpp>
#include <vector>

namespace Tetris
{
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

    int currentRotation;

    int x;
    int y;

    ftxui::Color color;

  public:
    Tetromino() : position({}), currentRotation(0), x(0), y(0), color(ftxui::Color::Default){};

    Tetromino(std::vector<std::vector<std::vector<Tetris::BlockType>>> position, ftxui::Color color)
    {
        this->position        = position;
        this->currentRotation = 0;
        this->color           = color;

        auto firstPosition = position.front();

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

        this->x = -minX;
        this->y = -minY;
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

    void move(int x, int y)
    {
        this->x += x;
        this->y += y;
    }

    void rotateRight()
    {
        this->currentRotation = this->rotateRight(this->currentRotation);
    }

    std::vector<std::vector<Tetris::BlockType>> get()
    {
        return this->position[this->currentRotation];
    }

    std::vector<std::vector<Tetris::BlockType>> get(int rotation)
    {
        return this->position[rotation];
    }

    ftxui::Color getColor()
    {
        return this->color;
    }

    int getX()
    {
        return this->x;
    }

    int getY()
    {
        return this->y;
    }

    int getRotation()
    {
        return this->currentRotation;
    }
};
} // namespace Tetris