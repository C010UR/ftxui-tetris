#include "t_game/t_tetromino.hpp"

namespace Tetris::Game
{
Tetromino::Tetromino(
    tetromino_rotations_t                         tetromino,
    std::vector<std::vector<Tetris::Game::Point>> wallKickOffsets,
    ftxui::Color                                  color,
    Tetris::Game::TetrominoType                   type
)
{
    this->tetromino       = tetromino;
    this->wallKickOffsets = wallKickOffsets;
    this->color           = color;
    this->type            = type;

    this->reset();
}

tetromino_rotations_t Tetromino::parseInputTetromino(std::vector<std::vector<std::string>> data, int size)
{
    tetromino_rotations_t result;

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

        tetromino_t tetromino;

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

tetromino_t Tetromino::getData(int rotation)
{
    return this->tetromino[rotation];
}

tetromino_t Tetromino::getData()
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

void Tetromino::move(const board_t &board, Tetris::Game::Point offset, Tetris::Game::RotationType rotation)
{
    auto wallKickTest = this->getWallKickTestData(rotation);

    this->currentPosition += offset;
    this->currentRotation = this->rotate(rotation);

    if (rotation == Tetris::Game::RotationType::NONE)
    {
        return;
    }

    auto data = this->getData();

    int height       = board.size() - 1;
    int width        = board[0].size() - 1;
    int frontCorners = 0, backCorners = 0;

    this->testPoints.clear();

    for (int row = 0; row < (int)data.size(); row++)
    {
        for (int col = 0; col < (int)data[row].size(); col++)
        {
            if (data[row][col] == Tetris::Game::BlockType::SPIN_LOOKUP_BACK
                || data[row][col] == Tetris::Game::BlockType::SPIN_LOOKUP_FRONT)
            {

                int newX = this->currentPosition.x + col;
                int newY = this->currentPosition.y + row;

                if (newX < 0 || newX > width || newY < 0 || newY > height
                    || board[newY][newX] == Tetris::Game::BoardBlockType::BLOCK)
                {
                    this->testPoints.push_back({(double)newX, (double)newY});

                    data[row][col] == Tetris::Game::BlockType::SPIN_LOOKUP_BACK ? backCorners++ : frontCorners++;
                }
            }
        }
    }

    this->testPoints.push_back({(double)backCorners, (double)frontCorners});

    bool wasLastWallKickTest = offset == wallKickTest[wallKickTest.size() - 1];

    if (wasLastWallKickTest && this->type == Tetris::Game::TetrominoType::T)
    {
        this->isLastMoveResultedInSpin = true;
        this->isMiniSpin               = false;
    }
    if (frontCorners + backCorners > 2)
    {
        this->isLastMoveResultedInSpin = true;
        this->isMiniSpin               = frontCorners == 1;
    }
    else
    {
        this->isLastMoveResultedInSpin = false;
        this->isMiniSpin               = false;
    }
}

bool Tetromino::isColliding(const board_t &board)
{

    auto data = this->getData();

    int height = board.size() - 1;
    int width  = board[0].size() - 1;

    for (int row = 0; row < (int)data.size(); row++)
    {
        for (int col = 0; col < (int)data[row].size(); col++)
        {
            if (data[row][col] == Tetris::Game::BlockType::BLOCK)
            {

                int newX = this->currentPosition.x + col;
                int newY = this->currentPosition.y + row;

                if (newX < 0 || newX > width || newY < 0 || newY > height
                    || board[newY][newX] == Tetris::Game::BoardBlockType::BLOCK)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

std::vector<Tetris::Game::Point> Tetromino::getWallKickTestData(Tetris::Game::RotationType rotation)
{
    if (rotation == Tetris::Game::RotationType::NONE)
    {
        return {
            {0, 0}
        };
    }

    auto first  = this->wallKickOffsets[this->currentRotation];
    auto second = this->wallKickOffsets[this->rotate(rotation)];

    for (int i = 0; i < (int)first.size(); i++)
    {
        first[i] -= second[i];
    }

    return first;
}

void Tetromino::reset()
{
    this->currentPosition = {0, 0};
    this->currentRotation = 0;
    this->testPoints.clear();
    this->resetSpinData();
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

    this->currentPosition
        = {(double)((int)(width / 2) - minX - (this->type == Tetris::Game::TetrominoType::O ? 0 : 1)), (double)-minY};
}

bool Tetromino::canMove(const board_t &board, Tetris::Game::Point offset)
{
    auto data = this->getData();

    int height = board.size() - 1;
    int width  = board[0].size() - 1;

    for (int row = 0; row < (int)data.size(); row++)
    {
        for (int col = 0; col < (int)data[row].size(); col++)
        {
            if (data[row][col] == Tetris::Game::BlockType::BLOCK)
            {
                int newX = this->currentPosition.x + offset.x + col;
                int newY = this->currentPosition.y + offset.y + row;

                if (newX < 0 || newX > width || newY < 0 || newY > height
                    || board[newY][newX] == Tetris::Game::BoardBlockType::BLOCK)
                {
                    return false;
                }
            }
        }
    }

    return true;
}

bool Tetromino::canRotate(const board_t &board, Tetris::Game::Point &offset, Tetris::Game::RotationType rotation)
{
    int height = board.size() - 1;
    int width  = board[0].size() - 1;

    auto data         = this->getData(this->rotate(rotation));
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

                if ((newX < 0 || newX > width || newY < 0 || newY > height
                     || board[newY][newX] == Tetris::Game::BoardBlockType::BLOCK)
                    && data[row][col] == Tetris::Game::BlockType::BLOCK)
                {
                    canMove = false;
                    break;
                }
            }

            if (!canMove)
            {
                break;
            }
        }
        if (canMove)
        {
            offset = wallKickTest[testEntry];
            return true;
        }
    }

    return false;
}

void Tetromino::resetSpinData()
{
    this->isLastMoveResultedInSpin = false;
    this->isMiniSpin               = false;
}

Tetris::Game::SpinType Tetromino::getSpinType()
{
    switch (this->type)
    {
    case TetrominoType::T:
        if (this->isLastMoveResultedInSpin)
        {
            return this->isMiniSpin ? Tetris::Game::SpinType::T_SPIN_MINI : Tetris::Game::SpinType::T_SPIN_FULL;
        }

        break;
    case TetrominoType::I:
    case TetrominoType::O:
    case TetrominoType::J:
    case TetrominoType::L:
    case TetrominoType::S:
    case TetrominoType::Z:
        break;
    }

    return Tetris::Game::SpinType::NONE;
}

double Tetromino::getRowsToObstacle(const board_t &board)
{
    double y = 0;

    while (this->canMove(board, {0, ++y}))
        ;

    --y;

    return y;
}
} // namespace Tetris::Game