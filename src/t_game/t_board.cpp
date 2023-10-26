#include "t_game/t_board.hpp"

#include "ftxui/dom/elements.hpp"
#include "ftxui/dom/node.hpp"
#include "ftxui/screen/color.hpp"
#include "t_game/t_enums.hpp"
#include "t_game/t_point.hpp"
#include "t_game/t_tetromino_factory.hpp"
#include "t_renderer/t_data_transformer.hpp"

#include <vector>

namespace Tetris::Game
{

bool Board::isLineFull(int line)
{
    for (int col = 0; col < (int)this->board[line].size(); col++)
    {
        if (this->board[line][col] == Tetris::Game::BoardBlockType::NONE)
        {
            return false;
        }
    }

    return true;
}

int Board::removeFullLines()
{
    std::vector<std::vector<ftxui::Color>>                 boardColor;
    std::vector<std::vector<Tetris::Game::BoardBlockType>> board;

    int fullLineCount = 0;

    for (int row = 0; row < (int)this->board.size(); row++)
    {
        if (this->isLineFull(row))
        {
            fullLineCount++;
            continue;
        }

        boardColor.push_back(this->boardColor[row]);
        board.push_back(this->board[row]);
    }

    this->board.clear();
    this->boardColor.clear();

    for (int row = 0; row < fullLineCount; row++)
    {
        this->board.push_back(std::vector<Tetris::Game::BoardBlockType>(width, Tetris::Game::BoardBlockType::NONE));
        this->boardColor.push_back(std::vector<ftxui::Color>(width, ftxui::Color::Default));
    }

    for (int row = 0; row < (int)board.size(); row++)
    {
        this->board.push_back(board[row]);
        this->boardColor.push_back(boardColor[row]);
    }

    return fullLineCount;
}

Board::Board(Tetris::Game::Tetromino tetromino)
{
    this->isGameOver = false;

    this->board.clear();
    this->boardColor.clear();

    for (int i = 0; i < height; i++)
    {
        this->board.push_back(std::vector<Tetris::Game::BoardBlockType>(width, Tetris::Game::BoardBlockType::NONE));
        this->boardColor.push_back(std::vector<ftxui::Color>(width, ftxui::Color::Default));
    }

    this->setCurrent(tetromino);
}

Tetris::Game::Tetromino *Board::getCurrent()
{
    return &this->current;
}

void Board::setCurrent(Tetris::Game::Tetromino tetromino)
{
    this->current = tetromino;
    this->current.reset(this->width);

    this->isGameOver = !this->canStore();
}

bool Board::tryRotateCurrent(Tetris::Game::RotationType rotation)
{
    Tetris::Game::Point offset;

    bool canRotate = this->current.canRotate(this->board, offset, rotation);

    if (canRotate)
    {
        this->current.move(offset, rotation);
    }

    return canRotate;
}

bool Board::canRotateCurrent(Tetris::Game::RotationType rotation)
{
    Tetris::Game::Point offset;

    return this->current.canRotate(this->board, offset, rotation);
}

bool Board::tryMoveCurrent(Tetris::Game::Point offset)
{
    bool canRotate = this->current.canMove(this->board, offset);

    if (canRotate)
    {
        this->current.move(offset);
    }

    return canRotate;
}

bool Board::canMoveCurrent(Tetris::Game::Point offset)
{
    return this->current.canMove(this->board, offset);
}

bool Board::canStore()
{
    return this->current.canMove(this->board, {0, 1});
}

bool Board::isBoardClear()
{
    for (int row = 0; row < (int)this->board.size(); row++)
    {
        for (int col = 0; col < (int)this->board[row].size(); col++)
        {
            if (this->board[row][col] == Tetris::Game::BoardBlockType::BLOCK)
            {
                return false;
            }
        }
    }

    return true;
}

int Board::store(Tetris::Game::Tetromino newTetromino)
{
    auto data = this->current.getData();

    int x = this->current.currentPosition.x;
    int y = this->current.currentPosition.y;

    for (int row = 0; row < (int)data.size(); row++)
    {
        for (int col = 0; col < (int)data[row].size(); col++)
        {
            if (data[row][col] == Tetris::Game::BlockType::BLOCK)
            {
                this->board[row + y][col + x]      = Tetris::Game::BoardBlockType::BLOCK;
                this->boardColor[row + y][col + x] = this->current.color;
            }
        }
    }

    this->setCurrent(newTetromino);
    return this->removeFullLines();
}

double Board::getRowsToObstacle()
{
    return this->current.getRowsToObstacle(this->board);
}

ftxui::Element Board::getDebugElement(double stepY)
{
    bool canMoveLeft  = this->current.canMove(this->board, {-1, 0});
    bool canMoveRight = this->current.canMove(this->board, {1, 0});
    bool canMoveDown  = this->current.canMove(this->board, {0, stepY});

    Tetris::Game::Point offsetLeft;
    bool canRotateLeft = this->current.canRotate(this->board, offsetLeft, Tetris::Game::RotationType::LEFT, true);

    Tetris::Game::Point offsetRight;
    bool canRotateRight = this->current.canRotate(this->board, offsetRight, Tetris::Game::RotationType::RIGHT, true);

    return ftxui::vbox(
        {ftxui::window(
             ftxui::text("Tetromino Movement"),
             ftxui::vbox({
                 Tetris::Renderer::KeyValue::create("Position", this->current.currentPosition),
                 Tetris::Renderer::KeyValue::create(
                     "Type", Tetris::Renderer::DataTransformer::toString(this->current.type)
                 ),
                 Tetris::Renderer::KeyValue::create("Color", this->current.color),
                 Tetris::Renderer::KeyValue::create("Can move left", canMoveLeft),
                 Tetris::Renderer::KeyValue::create("Can move right", canMoveRight),
                 Tetris::Renderer::KeyValue::create("Can move down", canMoveDown),
             })
         ),
         ftxui::window(
             ftxui::text("Tetromino Rotation"),
             ftxui::vbox({
                 Tetris::Renderer::KeyValue::create(
                     "Rotation", Tetris::Renderer::DataTransformer::transformRotation(this->current.currentRotation)
                 ),
                 Tetris::Renderer::KeyValue::create("Can rotate left", canRotateLeft),
                 Tetris::Renderer::KeyValue::create("Left rotation offset", offsetLeft),
                 Tetris::Renderer::KeyValue::create("Can rotate right", canRotateRight),
                 Tetris::Renderer::KeyValue::create("Right rotation offset", offsetRight),
                 Tetris::Renderer::KeyValue::create(
                     "Spin type", Tetris::Renderer::DataTransformer::toString(this->current.getSpinType())
                 ),
                 Tetris::Renderer::KeyValue::create(
                     "Test Spin type", Tetris::Renderer::DataTransformer::toString(this->current.getTestSpinType())
                 ),
             })
         ),
         ftxui::window(
             ftxui::text("Board"),
             ftxui::vbox({
                 Tetris::Renderer::KeyValue::create("Width", Board::width),
                 Tetris::Renderer::KeyValue::create("Height", Board::height),
                 Tetris::Renderer::KeyValue::create("Game over", this->isGameOver),
                 Tetris::Renderer::KeyValue::create("Is board clear", this->isBoardClear()),
                 Tetris::Renderer::KeyValue::create("Can store", !this->canStore()),
             })
         )}
    );
}

ftxui::Element Board::getElement(bool isEasyMode)
{
    ftxui::Canvas canvas = Tetris::Renderer::Canvas::create(Board::width, Board::height);

    Tetris::Renderer::Canvas::drawBoard(canvas, this->board, this->boardColor);
    Tetris::Renderer::Canvas::drawTetromino(canvas, this->current, false, false);

    if (isEasyMode)
    {
        double y = this->current.getRowsToObstacle(this->board);
        this->current.move({0, y});

        Tetris::Renderer::Canvas::drawTetromino(canvas, this->current, false, true);

        this->current.move({0, -y});
    }

    return ftxui::canvas(canvas) | ftxui::border | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, this->height);
}

} // namespace Tetris::Game