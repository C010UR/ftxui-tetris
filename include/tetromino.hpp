#pragma once

#include "ftxui/dom/canvas.hpp"
#include <ftxui/screen/color.hpp>
#include <utility>
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

    std::vector<std::vector<std::pair<int, int>>> wallKickData;

    int currentRotation;

    int x;
    int y;

    ftxui::Color color;

    bool _isEven;

  public:
    Tetromino()
        : position({}), wallKickData({}), currentRotation(0), x(0), y(0), color(ftxui::Color::Default), _isEven(false){};

    Tetromino(
        std::vector<std::vector<std::vector<Tetris::BlockType>>> position,
        std::vector<std::vector<std::pair<int, int>>>            wallKickData,
        ftxui::Color                                             color,
        bool                                                     isEven
    )
    {
        this->wallKickData    = wallKickData;
        this->position        = position;
        this->currentRotation = 0;
        this->color           = color;
        this->_isEven = isEven;

        this->x = 0;
        this->y = 0;
    }

    int getRotationIndex(Tetris::RotationType rotation)
    {
        if (rotation == Tetris::RotationType::NO_ROTATE)
        {
            return -1;
        }

        if (rotation == Tetris::RotationType::LEFT)
        {
            switch (this->currentRotation)
            {
            case 1:
                return 1;
            case 2:
                return 3;
            case 3:
                return 5;
            case 0:
                return 7;
            }
        }
        else
        {
            switch (this->currentRotation)
            {
            case 0:
                return 0;
            case 1:
                return 2;
            case 2:
                return 4;
            case 3:
                return 6;
            }
        }

        return -1;
    }

    std::vector<std::pair<int, int>> getRotationData(Tetris::RotationType rotation)
    {
        int rotationIndex = this->getRotationIndex(rotation);

        if (rotationIndex == -1)
        {
            return {
                {0, 0}
            };
        }

        return this->wallKickData[rotationIndex];
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

        this->x = (width / 2) - 1 - minX;
        this->y = -minY;
    }

    void move(int x, int y, Tetris::RotationType rotation = Tetris::RotationType::NO_ROTATE)
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

    int getX()
    {
        return this->x;
    }

    int getY()
    {
        return this->y;
    }

    void setX(int x)
    {
        this->x = x;
    }

    void setY(int y)
    {
        this->y = y;
    }

    bool isEven()
    {
        return this->_isEven;
    }
};
} // namespace Tetris