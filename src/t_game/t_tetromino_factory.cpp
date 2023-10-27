#include "t_game/t_tetromino_factory.hpp"

namespace Tetris::Game
{
Tetromino TetrominoFactory::get(TetrominoType type)
{
    // clang-format off
    switch (type)
    {
    case TetrominoType::I:
        return Tetromino(
            TetrominoFactory::I,
            TetrominoFactory::IWallKickData,
            Tetris::Renderer::CurrentTheme::IColor,
            type
        );
    case TetrominoType::O:
        return Tetromino(
            TetrominoFactory::O,
            TetrominoFactory::OWallKickData,
            Tetris::Renderer::CurrentTheme::OColor,
            type
        );
    case TetrominoType::T:
        return Tetromino(
            TetrominoFactory::T,
            TetrominoFactory::JLTSZWallKickData,
            Tetris::Renderer::CurrentTheme::TColor,
            type
        );
    case TetrominoType::J:
        return Tetromino(
            TetrominoFactory::J,
            TetrominoFactory::JLTSZWallKickData,
            Tetris::Renderer::CurrentTheme::JColor,
            type
        );
    case TetrominoType::L:
        return Tetromino(
            TetrominoFactory::L,
            TetrominoFactory::JLTSZWallKickData,
            Tetris::Renderer::CurrentTheme::LColor,
            type
        );
    case TetrominoType::S:
        return Tetromino(
            TetrominoFactory::S,
            TetrominoFactory::JLTSZWallKickData,
            Tetris::Renderer::CurrentTheme::SColor,
            type
        );
    case TetrominoType::Z:
        return Tetromino(
            TetrominoFactory::Z,
            TetrominoFactory::JLTSZWallKickData,
            Tetris::Renderer::CurrentTheme::ZColor,
            type
        );
        break;
    }
    // clang-format on

    return Tetromino();
}

std::vector<Tetromino> TetrominoFactory::getBag()
{
    std::vector<Tetromino> bag = {
        TetrominoFactory::get(TetrominoType::I),
        TetrominoFactory::get(TetrominoType::O),
        TetrominoFactory::get(TetrominoType::T),
        TetrominoFactory::get(TetrominoType::J),
        TetrominoFactory::get(TetrominoType::L),
        TetrominoFactory::get(TetrominoType::S),
        TetrominoFactory::get(TetrominoType::Z),
    };

    std::random_device rd;
    std::mt19937       g(rd());

    std::shuffle(bag.begin(), bag.end(), g);

    return bag;
}

std::vector<std::vector<Point>> TetrominoFactory::IWallKickData = {
    {{0, 0},   {-1, 0}, {2, 0},   {-1, 0}, {2, 0} },
    {{-1, 0},  {0, 0},  {0, 0},   {0, -1}, {0, 2} },
    {{-1, -1}, {1, -1}, {-2, -1}, {1, 0},  {-2, 0}},
    {{0, -1},  {0, -1}, {0, -1},  {0, 1},  {0, -2}}
};

std::vector<std::vector<Point>> TetrominoFactory::OWallKickData = {
    {{0, 0}},
    {{0, 1}},
    {{-1, 1}},
    {{-1, 0}},
};

std::vector<std::vector<Point>> TetrominoFactory::JLTSZWallKickData = {
    {{0, 0}, {0, 0},  {0, 0},  {0, 0},  {0, 0}  },
    {{0, 0}, {1, 0},  {1, 1},  {0, -2}, {1, -2} },
    {{0, 0}, {0, 0},  {0, 0},  {0, 0},  {0, 0}  },
    {{0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}}
};

// clang-format off
std::vector<std::vector<std::vector<BlockType>>> TetrominoFactory::I
    = Tetromino::parseInputTetromino({
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

std::vector<std::vector<std::vector<BlockType>>> TetrominoFactory::J
    = Tetromino::parseInputTetromino({
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

std::vector<std::vector<std::vector<BlockType>>> TetrominoFactory::L
    = Tetromino::parseInputTetromino({
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

std::vector<std::vector<std::vector<BlockType>>> TetrominoFactory::O
    = Tetromino::parseInputTetromino({
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

std::vector<std::vector<std::vector<BlockType>>> TetrominoFactory::S
    = Tetromino::parseInputTetromino({
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

std::vector<std::vector<std::vector<BlockType>>> TetrominoFactory::T
    = Tetromino::parseInputTetromino({
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

std::vector<std::vector<std::vector<BlockType>>> TetrominoFactory::Z 
    = Tetromino::parseInputTetromino({
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