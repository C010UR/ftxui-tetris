#pragma once

#include "ftxui/screen/color.hpp"
#include "tetromino.hpp"
#include <algorithm>
#include <random>
#include <stdexcept>
#include <vector>
namespace Tetris
{
enum TetrominoType
{
    I,
    O,
    T,
    J,
    L,
    S,
    Z
};

class TetrominoFactory
{
  public:
    static Tetromino generate(Tetris::TetrominoType type)
    {
        switch (type)
        {
        case Tetris::TetrominoType::I:
            return Tetris::Tetromino(
                {
                    {
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::BLK, BlockType::PVT, BlockType::BLK, BlockType::BLK},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     },
                    {
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::BLK, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::PVT, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::BLK, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::BLK, BlockType::NIL, BlockType::NIL},
                     },
                    {
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::BLK, BlockType::BLK, BlockType::PVT, BlockType::BLK, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     },
                    {
                     {BlockType::NIL, BlockType::NIL, BlockType::BLK, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::BLK, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::PVT, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::BLK, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     }
            },
                ftxui::Color::Cyan1
            );
        case Tetris::TetrominoType::O:
            return Tetris::Tetromino(
                {
                    {
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::PVT, BlockType::BLK, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::BLK, BlockType::BLK, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     },
                    {
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::PVT, BlockType::BLK, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::BLK, BlockType::BLK, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     },
                    {
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::PVT, BlockType::BLK, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::BLK, BlockType::BLK, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     },
                    {
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::PVT, BlockType::BLK, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::BLK, BlockType::BLK, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     }
            },
                ftxui::Color::Yellow1
            );
        case Tetris::TetrominoType::T:
            return Tetris::Tetromino(
                {
                    {
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::BLK, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::PVT, BlockType::BLK, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::BLK, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     },
                    {
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::BLK, BlockType::PVT, BlockType::BLK, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::BLK, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     },
                    {
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::BLK, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::BLK, BlockType::PVT, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::BLK, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     },
                    {
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::BLK, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::BLK, BlockType::PVT, BlockType::BLK, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     }
            },
                ftxui::Color::MediumPurple1
            );
        case Tetris::TetrominoType::J:
            return Tetris::Tetromino(
                {
                    {
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::BLK, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::PVT, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::BLK, BlockType::BLK, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     },
                    {
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::BLK, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::BLK, BlockType::PVT, BlockType::BLK, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     },
                    {
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::BLK, BlockType::BLK, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::PVT, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::BLK, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     },
                    {
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::BLK, BlockType::PVT, BlockType::BLK, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::BLK, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     }
            },
                ftxui::Color::Blue1
            );
        case Tetris::TetrominoType::L:
            return Tetris::Tetromino(
                {
                    {
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::BLK, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::PVT, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::BLK, BlockType::BLK, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     },
                    {
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::BLK, BlockType::PVT, BlockType::BLK, BlockType::NIL},
                     {BlockType::NIL, BlockType::BLK, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     },
                    {
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::BLK, BlockType::BLK, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::PVT, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::BLK, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     },
                    {
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::BLK, BlockType::NIL},
                     {BlockType::NIL, BlockType::BLK, BlockType::PVT, BlockType::BLK, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     }
            },
                ftxui::Color::Orange1
            );
        case Tetris::TetrominoType::S:
            return Tetris::Tetromino(
                {
                    {
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::PVT, BlockType::BLK, BlockType::NIL},
                     {BlockType::NIL, BlockType::BLK, BlockType::BLK, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     },
                    {
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::BLK, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::BLK, BlockType::PVT, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::BLK, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     },
                    {
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::BLK, BlockType::BLK, BlockType::NIL},
                     {BlockType::NIL, BlockType::BLK, BlockType::PVT, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     },
                    {
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::BLK, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::PVT, BlockType::BLK, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::BLK, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     }
            },
                ftxui::Color::Green1
            );
        case Tetris::TetrominoType::Z:
            return Tetris::Tetromino(
                {
                    {
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::BLK, BlockType::PVT, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::BLK, BlockType::BLK, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     },
                    {
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::BLK, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::BLK, BlockType::PVT, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::BLK, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     },
                    {
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::BLK, BlockType::BLK, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::PVT, BlockType::BLK, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     },
                    {
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::BLK, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::PVT, BlockType::BLK, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::BLK, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     }
            },
                ftxui::Color::Red1
            );
        default:
            throw std::invalid_argument("Tetromino type is not supported.");
        }
    }

    static std::vector<Tetromino> generateBag()
    {
        std::vector<Tetris::Tetromino> bag = {
            Tetris::TetrominoFactory::generate(Tetris::TetrominoType::I),
            Tetris::TetrominoFactory::generate(Tetris::TetrominoType::J),
            Tetris::TetrominoFactory::generate(Tetris::TetrominoType::L),
            Tetris::TetrominoFactory::generate(Tetris::TetrominoType::O),
            Tetris::TetrominoFactory::generate(Tetris::TetrominoType::S),
            Tetris::TetrominoFactory::generate(Tetris::TetrominoType::T),
            Tetris::TetrominoFactory::generate(Tetris::TetrominoType::Z),
        };

        std::random_device rd;
        std::mt19937       g(rd());

        std::shuffle(bag.begin(), bag.end(), g);

        return bag;
    }
};
} // namespace Tetris