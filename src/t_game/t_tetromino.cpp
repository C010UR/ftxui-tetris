#include "t_game/t_tetromino.hpp"

namespace Tetris::Game
{
Tetromino::Tetromino(
    std::vector<std::vector<std::vector<Tetris::Game::BlockType>>> tetromino,
    std::vector<std::vector<Tetris::Game::Point>>                  wallKickOffsets,
    ftxui::Color                                                   color,
    Tetris::Game::TetrominoType                                    type
)
{
    this->tetromino       = tetromino;
    this->wallKickOffsets = wallKickOffsets;
    this->color           = color;
    this->type            = type;

    this->reset();
}

std::vector<std::vector<std::vector<Tetris::Game::BlockType>>> Tetromino::parseInputTetromino(
    std::vector<std::vector<std::string>> data, int size
)
{
    std::vector<std::vector<std::vector<Tetris::Game::BlockType>>> result;

    if (data.size() != 4)
    {
        throw std::invalid_argument("Tetromino does not have 4 rotations");
    }

    for (int rotation = 0; rotation < 4; rotation++)
    {
        if ((int)data[rotation].size() != size)
        {
            throw std::invalid_argument("Height of the actual tetromino is not valid");
        }

        std::vector<std::vector<Tetris::Game::BlockType>> tetromino;

        for (int y = 0; y < size; y++)
        {
            std::vector<Tetris::Game::BlockType> row;

            if ((int)data[rotation][y].size() != size)
            {
                throw std::invalid_argument("Width of the actual tetromino is not valid");
            }

            for (int x = 0; x < size; x++)
            {
                switch (data[rotation][y][x])
                {
                case ' ':
                    row.push_back(Tetris::Game::BlockType::NONE);
                    break;
                case '+':
                    row.push_back(Tetris::Game::BlockType::SPIN_LOOKUP_FRONT);
                    break;
                case '-':
                    row.push_back(Tetris::Game::BlockType::SPIN_LOOKUP_BACK);
                    break;
                default:
                    row.push_back(Tetris::Game::BlockType::BLOCK);
                }
            }

            tetromino.push_back(row);
        }

        result.push_back(tetromino);
    }

    return result;
}

std::vector<std::vector<Tetris::Game::BlockType>> Tetromino::getData(int rotation)
{
    return this->tetromino[rotation];
}

std::vector<std::vector<Tetris::Game::BlockType>> Tetromino::getData()
{
    return this->getData(this->currentRotation);
}

int Tetromino::rotate(Tetris::Game::RotationType rotation)
{
    switch (rotation)
    {
    case Tetris::Game::RotationType::LEFT:
        return this->currentRotation == 0 ? (int)this->tetromino.size() - 1 : this->currentRotation - 1;
    case Tetris::Game::RotationType::RIGHT:
        return this->currentRotation == (int)this->tetromino.size() - 1 ? 0 : this->currentRotation + 1;
    default:
        break;
    }

    return this->currentRotation;
}

void Tetromino::move(Tetris::Game::Point offset, Tetris::Game::RotationType rotation)
{
    this->isLastMoveResultedInSpin = this->testIsLastMoveResultedInSpin;
    this->isMiniSpin               = this->testIsMiniSpin;

    this->currentPosition += offset;
    this->currentRotation = this->rotate(rotation);
}

std::vector<Tetris::Game::Point> Tetromino::getWallKickTestData(Tetris::Game::RotationType rotation)
{
    if (rotation == Tetris::Game::RotationType::NONE)
    {
        return {
            {0, 0}
        };
    }

    int nextRotation = this->rotate(rotation);

    auto first  = this->wallKickOffsets[this->currentRotation];
    auto second = this->wallKickOffsets[nextRotation];

    for (int i = 0; i < (int)first.size(); i++)
    {
        first[i] -= second[i];
    }

    return first;
}

void Tetromino::reset()
{
    this->currentPosition              = {0, 0};
    this->currentRotation              = 0;
    this->isLastMoveResultedInSpin     = false;
    this->isMiniSpin                   = false;
    this->testIsLastMoveResultedInSpin = false;
    this->testIsLastMoveResultedInSpin = false;
}

void Tetromino::reset(int width)
{
    this->reset();

    auto tetromino = this->getData();

    int minX = INT_MAX;
    int maxX = 0;
    int minY = INT_MAX;

    for (int row = 0; row < (int)tetromino.size(); row++)
    {
        for (int col = 0; col < (int)tetromino[row].size(); col++)
        {
            if (tetromino[row][col] == BlockType::BLOCK && minY > row)
            {
                minY = row;
            }

            if (tetromino[row][col] == BlockType::BLOCK && maxX < col)
            {
                maxX = col;
            }

            if (tetromino[row][col] == BlockType::BLOCK && minX > col)
            {
                minX = col;
            }
        }
    }

    this->currentPosition = {(double)((int)(width / 2) - minX - 1), (double)-minY};
}

bool Tetromino::canMove(const std::vector<std::vector<Tetris::Game::BoardBlockType>> &board, Tetris::Game::Point offset)
{
    this->testIsLastMoveResultedInSpin = false;
    this->testIsMiniSpin               = false;

    auto data = this->getData();

    int height = board.size() - 1;
    int width  = board[0].size() - 1;

    for (int row = 0; row < (int)data.size(); row++)
    {
        for (int col = 0; col < (int)data[row].size(); col++)
        {
            if (data[row][col] != Tetris::Game::BlockType::BLOCK)
            {
                continue;
            }

            int newX = this->currentPosition.x + offset.x + col;
            int newY = this->currentPosition.y + offset.y + row;

            if (newX < 0 || newX > width || newY < 0 || newY > height
                || board[newY][newX] == Tetris::Game::BoardBlockType::BLOCK)
            {
                return false;
            }
        }
    }

    return true;
}

bool Tetromino::canRotate(
    const std::vector<std::vector<Tetris::Game::BoardBlockType>> &board,
    Tetris::Game::Point                                          &offset,
    Tetris::Game::RotationType                                    rotation
)
{
    this->testIsLastMoveResultedInSpin = false;
    this->testIsMiniSpin               = false;

    int newRotation = this->rotate(rotation);

    int height = board.size() - 1;
    int width  = board[0].size() - 1;

    int frontCorners = 0;
    int backCorners  = 0;

    auto data         = this->getData(newRotation);
    auto wallKickTest = this->getWallKickTestData(rotation);

    for (int testEntry = 0; testEntry < (int)wallKickTest.size(); testEntry++)
    {
        bool canMove = true;

        for (int row = 0; row < (int)data.size(); row++)
        {
            for (int col = 0; col < (int)data[row].size(); col++)
            {
                if (data[row][col] == Tetris::Game::BlockType::NONE)
                {
                    continue;
                }

                int newX = this->currentPosition.x + offset.x + col + wallKickTest[testEntry].x;
                int newY = this->currentPosition.y + offset.y + row + wallKickTest[testEntry].y;

                if (newX < 0 || newX > width || newY < 0 || newY > height
                    || board[newY][newX] == Tetris::Game::BoardBlockType::BLOCK)
                {
                    switch (data[row][col])
                    {
                    case BlockType::BLOCK:
                        canMove = false;
                        break;
                    case BlockType::SPIN_LOOKUP_FRONT:
                        frontCorners++;
                        break;
                    case BlockType::SPIN_LOOKUP_BACK:
                        backCorners++;
                        break;
                    default:
                        break;
                    }

                    if (!canMove)
                    {
                        break;
                    }
                }
            }

            if (!canMove)
            {
                break;
            }
        }

        if (canMove)
        {
            if (wallKickTest[testEntry] == Tetris::Game::Point{1, -2}
                || wallKickTest[testEntry] == Tetris::Game::Point{-1, -2})
            {
                this->testIsLastMoveResultedInSpin = true;
                this->testIsMiniSpin               = false;
            }
            else if (frontCorners + backCorners > 2)
            {
                this->testIsLastMoveResultedInSpin = true;
                this->testIsMiniSpin               = frontCorners == 1;
            }

            offset += wallKickTest[testEntry];
            return true;
        }
    }

    return false;
}

double Tetromino::getRowsToObstacle(const std::vector<std::vector<Tetris::Game::BoardBlockType>> &board)
{
    double y = 0;

    while (this->canMove(board, {0, ++y}))
        ;

    --y;

    return y;
}
} // namespace Tetris::Game