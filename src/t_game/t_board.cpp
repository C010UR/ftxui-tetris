#include "t_game/t_board.hpp"

#include "ftxui/dom/elements.hpp"
#include "ftxui/dom/node.hpp"
#include "ftxui/screen/screen.hpp"
#include "t_renderer/t_key_value.hpp"

namespace Tetris::Game
{

bool Board::isLineFull(int line)
{
    for (int col = 0; col < (int)this->board[line].size(); col++)
    {
        if (this->board[line][col] == BoardBlockType::NONE)
        {
            return false;
        }
    }

    return true;
}

int Board::removeFullLines()
{
    std::vector<std::vector<ftxui::Color>> boardColor;
    board_t                                board;

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
        this->board.push_back(std::vector<BoardBlockType>(width, BoardBlockType::NONE));
        this->boardColor.push_back(std::vector<ftxui::Color>(width, ftxui::Color::Default));
    }

    for (int row = 0; row < (int)board.size(); row++)
    {
        this->board.push_back(board[row]);
        this->boardColor.push_back(boardColor[row]);
    }

    return fullLineCount;
}

Board::Board(Tetromino tetromino)
{
    this->isGameOver = false;

    this->board.clear();
    this->boardColor.clear();

    for (int i = 0; i < height; i++)
    {
        this->board.push_back(std::vector<BoardBlockType>(width, BoardBlockType::NONE));
        this->boardColor.push_back(std::vector<ftxui::Color>(width, ftxui::Color::Default));
    }

    this->setCurrent(tetromino);
}

Tetromino *Board::getCurrent()
{
    return &this->current;
}

void Board::setCurrent(Tetromino tetromino)
{
    this->current = tetromino;
    this->current.reset(this->width);

    this->isGameOver = this->current.isColliding(this->board);
}

bool Board::tryRotateCurrent(RotationType rotation)
{
    Point offset;

    bool canRotate = this->current.canRotate(this->board, offset, rotation);

    if (canRotate)
    {
        this->current.move(this->board, offset, rotation);
    }

    return canRotate;
}

bool Board::canRotateCurrent(RotationType rotation)
{
    Point offset;

    return this->current.canRotate(this->board, offset, rotation);
}

bool Board::tryMoveCurrent(Point offset)
{
    bool canRotate = this->current.canMove(this->board, offset);

    if (canRotate)
    {
        this->current.move(this->board, offset);
    }

    return canRotate;
}

bool Board::canMoveCurrent(Point offset)
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
            if (this->board[row][col] == BoardBlockType::BLOCK)
            {
                return false;
            }
        }
    }

    return true;
}

int Board::store(Tetromino newTetromino)
{
    auto data = this->current.getData();

    int x = this->current.currentPosition.x;
    int y = this->current.currentPosition.y;

    for (int row = 0; row < (int)data.size(); row++)
    {
        for (int col = 0; col < (int)data[row].size(); col++)
        {
            if (data[row][col] == BlockType::BLOCK)
            {
                this->board[row + y][col + x]      = BoardBlockType::BLOCK;
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

    Point offsetLeft;
    bool  canRotateLeft = this->current.canRotate(this->board, offsetLeft, RotationType::LEFT);

    Point offsetRight;
    bool  canRotateRight = this->current.canRotate(this->board, offsetRight, RotationType::RIGHT);

    ftxui::Elements testPoints;

    for (int i = 0; i < (int)this->current.testPoints.size(); i++)
    {
        testPoints.push_back(
            Tetris::Renderer::KeyValue::create("Point " + std::to_string(i + 1), this->current.testPoints[i])
        );
    }

    return ftxui::hbox(
        {ftxui::vbox(
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
                          "Rotation",
                          Tetris::Renderer::DataTransformer::transformRotation(this->current.currentRotation)
                      ),
                      Tetris::Renderer::KeyValue::create("Can rotate left", canRotateLeft),
                      Tetris::Renderer::KeyValue::create("Left rotation offset", offsetLeft),
                      Tetris::Renderer::KeyValue::create("Can rotate right", canRotateRight),
                      Tetris::Renderer::KeyValue::create("Right rotation offset", offsetRight),
                      Tetris::Renderer::KeyValue::create(
                          "Spin type", Tetris::Renderer::DataTransformer::toString(this->current.getSpinType())
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
         ) | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 40),
         ftxui::vbox({ftxui::window(ftxui::text("Test points"), ftxui::vbox(testPoints))})
             | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 20)}
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
        this->current.move(this->board, {0, y});

        Tetris::Renderer::Canvas::drawTetromino(canvas, this->current, false, true);

        this->current.move(this->board, {0, -y});
    }

    return ftxui::canvas(canvas) | ftxui::border | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, this->height);
}

} // namespace Tetris::Game