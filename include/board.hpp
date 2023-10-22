#pragma once

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/task.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>
#include <optional>
#include <processthreadsapi.h>
#include <string>
#include <vector>

#include "canvas.hpp"
#include "enums.hpp"
#include "output_helper.hpp"
#include "tetromino.hpp"
#include "tetromino_factory.hpp"

namespace Tetris
{

class Board
{
  private:
    std::vector<std::vector<ftxui::Color>> boardColor;
    std::vector<std::vector<bool>>         board;

    Tetris::Tetromino current;

    bool gameOver;

  public:
    inline static const int width  = 10;
    inline static const int height = 20;

    Board() : gameOver(true)
    {
    }

    Board(Tetris::Tetromino tetromino)

    {
        this->gameOver = false;

        this->board.clear();
        this->boardColor.clear();

        for (int i = 0; i < height; i++)
        {
            this->board.push_back(std::vector<bool>(width, false));
            this->boardColor.push_back(std::vector<ftxui::Color>(width, ftxui::Color::Default));
        }

        this->setCurrent(tetromino);
    }

    Tetris::Tetromino *getCurrent()
    {
        return &this->current;
    }

    void setCurrent(Tetris::Tetromino tetromino)
    {
        this->current = tetromino;
        this->current.reset(this->width);

        if (!this->canMove(0, 1))
        {
            this->gameOver = true;
        }
    }

    bool canRotate(int &x, int &y, Tetris::RotationType rotation)
    {
        if (!this->board.size() || !this->board[0].size())
        {
            return false;
        }

        auto tetromino = this->current;

        int currentRotation = tetromino.getRotation();

        switch (rotation)
        {
        case Tetris::RotationType::LEFT:
            currentRotation = tetromino.rotateLeft(currentRotation);
            break;
        case Tetris::RotationType::RIGHT:
            currentRotation = tetromino.rotateRight(currentRotation);
            break;
        default:
            break;
        }

        auto data = tetromino.getMatrix(currentRotation);

        if (!data.size() || !data[0].size())
        {
            return false;
        }

        auto wallKickData = tetromino.getRotationData(rotation);

        for (auto wallKickEntry : wallKickData)
        {
            bool isCanMove = true;
            for (int i = 0; i < (int)data.size(); i++)
            {
                for (int j = 0; j < (int)data[0].size(); j++)
                {
                    if (data[i][j] == Tetris::BlockType::NIL)
                    {
                        continue;
                    }

                    int nextX = (int)(tetromino.getX() + x) + wallKickEntry.first + j;
                    int nextY = (int)(tetromino.getY() + y) + wallKickEntry.second + i;

                    if (nextX < 0 || nextX + 1 > (int)this->board[0].size())
                    {
                        isCanMove = false;

                        break;
                    }

                    if (nextY < 0 || nextY + 1 > (int)this->board.size())
                    {
                        isCanMove = false;

                        break;
                    }

                    if (this->board[nextY][nextX])
                    {
                        isCanMove = false;

                        break;
                    }
                }

                if (!isCanMove)
                {
                    break;
                }
            }

            if (isCanMove)
            {
                x += wallKickEntry.first;
                y += wallKickEntry.second;

                return true;
            }
        }

        return false;
    }

    bool canMove(double x, double y)
    {
        if (!this->board.size() || !this->board[0].size())
        {
            return false;
        }

        auto tetromino = this->current;
        auto data      = tetromino.getMatrix();

        if (!data.size() || !data[0].size())
        {
            return false;
        }

        for (int i = 0; i < (int)data.size(); i++)
        {
            for (int j = 0; j < (int)data[0].size(); j++)
            {
                if (data[i][j] == Tetris::BlockType::NIL)
                {
                    continue;
                }

                int currentX = (int)(tetromino.getX() + x) + j;
                int currentY = (int)(tetromino.getY() + y) + i;

                if (currentX < 0 || currentX + 1 > (int)this->board[0].size())
                {
                    return false;
                }

                if (currentY < 0 || currentY + 1 > (int)this->board.size())
                {
                    return false;
                }

                if (this->board[currentY][currentX])
                {
                    return false;
                }
            }
        }

        return true;
    }

    int getHardDropY()
    {
        double y = 0;

        while (this->canMove(0, ++y))
            ;

        --y;

        return y;
    }

    bool canStore()
    {
        return !this->canMove(0, 1);
    }

    bool isBoardClear()
    {
        for (int i = 0; i < (int)this->board.size(); i++)
        {
            for (int j = 0; j < (int)this->board[i].size(); j++)
            {
                if (this->board[i][j])
                {
                    return false;
                }
            }
        }

        return true;
    }

  private:
    void _store(Tetris::Tetromino newTetromino)
    {
        auto data = this->current.getMatrix();

        int          x     = this->current.getX();
        int          y     = this->current.getY();
        ftxui::Color color = this->current.getColor();

        for (int i = 0; i < (int)data.size(); i++)
        {
            for (int j = 0; j < (int)data[i].size(); j++)
            {
                if (data[i][j] == Tetris::BlockType::NIL)
                {
                    continue;
                }

                this->board[i + y][j + x]      = true;
                this->boardColor[i + y][j + x] = color;
            }
        }

        this->setCurrent(newTetromino);
    }

    bool isLineFull(int line)
    {
        for (int i = 0; i < (int)this->board[line].size(); i++)
        {
            if (!this->board[line][i])
            {
                return false;
            }
        }

        return true;
    }

    void removeLine(int line)
    {
        if (line == 0)
        {
            for (int i = 0; i < (int)this->board[line].size(); i++)
            {
                this->board[line][i]      = false;
                this->boardColor[line][i] = ftxui::Color::Default;
            }

            return;
        }

        for (int i = line; i > 0; i--)
        {
            for (int j = 0; j < (int)this->board[i].size(); j++)
            {
                this->board[i][j]      = this->board[i - 1][j];
                this->boardColor[i][j] = this->boardColor[i - 1][j];
            }
        }
    }

    int _updateLines()
    {
        int fullLineCount = 0;

        for (int i = 0; i < (int)board.size(); i++)
        {
            if (this->isLineFull(i))
            {
                fullLineCount++;
                this->removeLine(i);
            }
        }

        return fullLineCount;
    }

  public:
    int store(Tetris::Tetromino newTetromino)
    {
        this->_store(newTetromino);
        return this->_updateLines();
    }

    ftxui::Element getDebugElement(double x, double y)
    {
        bool canMoveLeft  = this->canMove(-x, 0);
        bool canMoveRight = this->canMove(x, 0);
        bool canMoveDown  = this->canMove(0, y);

        int rX = 0, rY = 0;

        bool canRotateLeft = this->canRotate(rX, rY, Tetris::RotationType::LEFT);

        rX = 0;
        rY = 0;

        bool canRotateRight = this->canRotate(rX, rY, Tetris::RotationType::RIGHT);
        return ftxui::vbox(
            {ftxui::window(
                 ftxui::text("Tetromino Movement"),
                 ftxui::vbox({
                     Tetris::OutputHelper::getKeyValueText("X", this->current.getX()),
                     Tetris::OutputHelper::getKeyValueText("y", this->current.getY()),
                     Tetris::OutputHelper::getKeyValueText("Colour", this->current.getColor()),
                     Tetris::OutputHelper::getKeyValueText("Can move left", canMoveLeft),
                     Tetris::OutputHelper::getKeyValueText("Can move right", canMoveRight),
                     Tetris::OutputHelper::getKeyValueText("Can move down", canMoveDown),
                     Tetris::OutputHelper::getKeyValueText(
                         "TetrominoType", Tetris::OutputHelper::enumToString(this->current.getTetrominoType())
                     ),
                 })
             ),
             ftxui::window(
                 ftxui::text("Tetromino Rotation"),
                 ftxui::vbox({
                     Tetris::OutputHelper::getKeyValueText("Current Rotation", this->current.getRotation()),
                     Tetris::OutputHelper::getKeyValueText("Can rotate left", canRotateLeft),
                     Tetris::OutputHelper::getKeyValueText("Can rotate right", canRotateRight),
                 })
             )}
        );
    }

    ftxui::Element getBoardElement(bool isEasyMode = false)
    {
        ftxui::Canvas canvas = Tetris::Canvas::createCanvas(this->width, this->height);

        Tetris::Canvas::drawBoard(canvas, this->board, this->boardColor);

        if (!this->gameOver)
        {
            Tetris::Canvas::drawTetromino(canvas, this->current, false);

            if (isEasyMode)
            {
                int y = this->getHardDropY();

                this->current.move(0, y);

                Tetris::Canvas::drawTetromino(canvas, this->current, false, true);

                this->current.move(0, -y);
            }
        }

        return ftxui::canvas(canvas) | ftxui::border | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, this->height);
    }

    void setGameOver(bool gameOver)
    {
        this->gameOver = gameOver;
    }

    bool isGameOver()
    {
        return this->gameOver;
    }
};
} // namespace Tetris
