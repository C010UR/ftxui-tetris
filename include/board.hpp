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
#include "output_helper.hpp"
#include "score.hpp"
#include "tetromino.hpp"
#include "tetromino_factory.hpp"

namespace Tetris
{
enum TriggerType
{
    MOVE_LEFT,
    MOVE_RIGHT,
    SOFT_DROP,
    HARD_DROP,
    ROTATE_LEFT,
    ROTATE_RIGHT,
    SWAP_HOLD,
    NO_TRIGGER
};
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

        this->board = {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 1, 1, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            {1, 1, 1, 0, 1, 0, 1, 1, 1, 0},
            {1, 1, 0, 0, 1, 0, 0, 1, 1, 0},
            {1, 1, 1, 0, 1, 0, 1, 1, 1, 0},
        };

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

        if (!this->canMove(0, 0))
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

                    int nextX = tetromino.getX() + x + wallKickEntry.first + j;
                    int nextY = tetromino.getY() + y + wallKickEntry.second + i;

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

    bool canMove(int x, int y)
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

                int currentX = tetromino.getX() + x + j;
                int currentY = tetromino.getY() + y + i;

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
        int y = 0;

        while (this->canMove(0, ++y))
            ;

        --y;

        return y;
    }

    bool canStore()
    {
        return !this->canMove(0, 1);
    }

  private:
    void store(Tetris::Tetromino newTetromino)
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

    int updateLines()
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
    void store(Tetris::Score &score, Tetris::Tetromino newTetromino, Tetris::TriggerType trigger, int level)
    {
        this->store(newTetromino);
        this->updateLines();
    }

    ftxui::Element getDebugElement()
    {
        bool canMoveLeft  = this->canMove(-1, 0);
        bool canMoveRight = this->canMove(1, 0);
        bool canMoveDown  = this->canMove(0, 1);

        int x = 0, y = 0;

        bool canRotateLeft = this->canRotate(x, y, Tetris::RotationType::LEFT);
        x                  = 0;
        y                  = 0;

        bool canRotateRight = this->canRotate(x, y, Tetris::RotationType::RIGHT);

        std::string tetrominoType = "";

        switch (this->current.getTetrominoType())
        {
        case Tetris::TetrominoType::I:
            tetrominoType = "I";
            break;
        case Tetris::TetrominoType::O:
            tetrominoType = "O";
            break;
        case Tetris::TetrominoType::J:
            tetrominoType = "J";
            break;
        case Tetris::TetrominoType::L:
            tetrominoType = "L";
            break;
        case Tetris::TetrominoType::S:
            tetrominoType = "S";
            break;
        case Tetris::TetrominoType::T:
            tetrominoType = "T";
            break;
        case Tetris::TetrominoType::Z:
            tetrominoType = "Z";
            break;
        default:
            tetrominoType = "<NULL>";
        }

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
                     Tetris::OutputHelper::getKeyValueText("TetrominoType", tetrominoType),
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

        return ftxui::canvas(canvas) | ftxui::border;
    }

    bool isGameOver()
    {
        return this->gameOver;
    }
};
} // namespace Tetris
