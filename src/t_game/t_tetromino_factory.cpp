#include "t_game/t_tetromino_factory.hpp"

namespace Tetris::Game
{
Tetris::Game::Tetromino TetrominoFactory::get(Tetris::Game::TetrominoType type)
{
    // clang-format off
    switch (type)
    {
    case TetrominoType::I:
        return Tetris::Game::Tetromino(
            TetrominoFactory::I,
            TetrominoFactory::IWallKickData,
            Tetris::Renderer::Color::IColor,
            type
        );
    case TetrominoType::O:
        return Tetris::Game::Tetromino(
            TetrominoFactory::O,
            TetrominoFactory::OWallKickData,
            Tetris::Renderer::Color::OColor,
            type
        );
    case TetrominoType::T:
        return Tetris::Game::Tetromino(
            TetrominoFactory::T,
            TetrominoFactory::JLTSZWallKickData,
            Tetris::Renderer::Color::TColor,
            type
        );
    case TetrominoType::J:
        return Tetris::Game::Tetromino(
            TetrominoFactory::J,
            TetrominoFactory::JLTSZWallKickData,
            Tetris::Renderer::Color::JColor,
            type
        );
    case TetrominoType::L:
        return Tetris::Game::Tetromino(
            TetrominoFactory::L,
            TetrominoFactory::JLTSZWallKickData,
            Tetris::Renderer::Color::LColor,
            type
        );
    case TetrominoType::S:
        return Tetris::Game::Tetromino(
            TetrominoFactory::S,
            TetrominoFactory::JLTSZWallKickData,
            Tetris::Renderer::Color::SColor,
            type
        );
    case TetrominoType::Z:
        return Tetris::Game::Tetromino(
            TetrominoFactory::Z,
            TetrominoFactory::JLTSZWallKickData,
            Tetris::Renderer::Color::ZColor,
            type
        );
        break;
    }
    // clang-format on

    return Tetris::Game::Tetromino();
}

std::vector<Tetris::Game::Tetromino> TetrominoFactory::getBag()
{
    std::vector<Tetris::Game::Tetromino> bag = {
        TetrominoFactory::get(Tetris::Game::TetrominoType::I),
        TetrominoFactory::get(Tetris::Game::TetrominoType::O),
        TetrominoFactory::get(Tetris::Game::TetrominoType::T),
        TetrominoFactory::get(Tetris::Game::TetrominoType::J),
        TetrominoFactory::get(Tetris::Game::TetrominoType::L),
        TetrominoFactory::get(Tetris::Game::TetrominoType::S),
        TetrominoFactory::get(Tetris::Game::TetrominoType::Z),
    };

    std::random_device rd;
    std::mt19937       g(rd());

    std::shuffle(bag.begin(), bag.end(), g);

    return bag;
}

std::vector<std::vector<Tetris::Game::Point>> TetrominoFactory::IWallKickData = {
    {{0, 0},   {-1, 0}, {2, 0},   {-1, 0}, {2, 0} },
    {{-1, 0},  {0, 0},  {0, 0},   {0, -1}, {0, 2} },
    {{-1, -1}, {1, -1}, {-2, -1}, {1, 0},  {-2, 0}},
    {{0, -1},  {0, -1}, {0, -1},  {0, 1},  {0, -2}}
};

std::vector<std::vector<Tetris::Game::Point>> TetrominoFactory::OWallKickData = {
    {{0, 0}},
    {{0, 1}},
    {{-1, 1}},
    {{-1, 0}},
};

std::vector<std::vector<Tetris::Game::Point>> TetrominoFactory::JLTSZWallKickData = {
    {{0, 0}, {0, 0},  {0, 0},  {0, 0},  {0, 0}  },
    {{0, 0}, {1, 0},  {1, 1},  {0, -2}, {1, -2} },
    {{0, 0}, {0, 0},  {0, 0},  {0, 0},  {0, 0}  },
    {{0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}}
};

// clang-format off
std::vector<std::vector<std::vector<Tetris::Game::BlockType>>> TetrominoFactory::I
    = Tetris::Game::Tetromino::parseInputTetromino({
        {
            {"     "},
            {"     "},
            {" IIII"},
            {"     "},
            {"     "}
        },
        {
            {"     "},
            {"  I  "},
            {"  I  "},
            {"  I  "},
            {"  I  "}
        },
        {
            {"     "},
            {"     "},
            {"IIII "},
            {"     "},
            {"     "}
        },
        {
            {"  I  "},
            {"  I  "},
            {"  I  "},
            {"  I  "},
            {"     "}
        }
    }, 5);

std::vector<std::vector<std::vector<Tetris::Game::BlockType>>> TetrominoFactory::J
    = Tetris::Game::Tetromino::parseInputTetromino({
        {
            {"J  "},
            {"JJJ"},
            {"   "}
        },
        {
            {" JJ"},
            {" J "},
            {" J "}
        },
        {
            {"   "},
            {"JJJ"},
            {"  J"}
        },
        {
            {" J "},
            {" J "},
            {"JJ "}
        }
    }, 3);

std::vector<std::vector<std::vector<Tetris::Game::BlockType>>> TetrominoFactory::L
    = Tetris::Game::Tetromino::parseInputTetromino({
        {
            {"  L"},
            {"LLL"},
            {"   "}
        },
        {
            {" L "},
            {" L "},
            {" LL"}
        },
        {
            {"   "},
            {"LLL"},
            {"L  "}
        },
        {
            {"LL "},
            {" L "},
            {" L "}
        }
    }, 3);

std::vector<std::vector<std::vector<Tetris::Game::BlockType>>> TetrominoFactory::O
    = Tetris::Game::Tetromino::parseInputTetromino({
        {
            {" OO"},
            {" OO"},
            {"   "}
        },
        {
            {"   "},
            {" OO"},
            {" OO"}
        },
        {
            {"   "},
            {"OO "},
            {"OO "}
        },
        {
            {"OO "},
            {"OO "},
            {"   "}
        }
    }, 3);

std::vector<std::vector<std::vector<Tetris::Game::BlockType>>> TetrominoFactory::S
    = Tetris::Game::Tetromino::parseInputTetromino({
        {
            {" SS"},
            {"SS "},
            {"   "}
        },
        {
            {" S "},
            {" SS"},
            {"  S"}
        },
        {
            {"   "},
            {" SS"},
            {"SS "}
        },
        {
            {"S  "},
            {"SS "},
            {" S "}
        }
    }, 3);

std::vector<std::vector<std::vector<Tetris::Game::BlockType>>> TetrominoFactory::T
    = Tetris::Game::Tetromino::parseInputTetromino({
        {
            {"+T+"},
            {"TTT"},
            {"- -"}
        },
        {
            {"-T+"},
            {" TT"},
            {"-T+"}
        },
        {
            {"- -"},
            {"TTT"},
            {"+T+"}
        },
        {
            {"+T-"},
            {"TT "},
            {"+T-"}
        }
    }, 3);

std::vector<std::vector<std::vector<Tetris::Game::BlockType>>> TetrominoFactory::Z 
    = Tetris::Game::Tetromino::parseInputTetromino({
        {
            {"ZZ "},
            {" ZZ"},
            {"   "}
        },
        {
            {"  Z"},
            {" ZZ"},
            {" Z "}
        },
        {
            {"   "},
            {"ZZ "},
            {" ZZ"}
        },
        {
            {" Z "},
            {"ZZ "},
            {"Z  "}
        }
    }, 3);
// clang-format on
} // namespace Tetris::Game