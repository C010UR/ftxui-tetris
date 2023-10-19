#pragma once

#include "ftxui/screen/color.hpp"
#include "tetromino.hpp"
#include <algorithm>
#include <random>
#include <stdexcept>
#include <utility>
#include <vector>
namespace Tetris
{

class TetrominoFactory
{
  public:
    static Tetromino generate(Tetris::TetrominoType type)
    {
        std::vector<std::vector<std::pair<int, int>>> JLTSZWallKick = {
            {{0, 0}, {0, 0},  {0, 0},  {0, 0},  {0, 0}  },
            {{0, 0}, {1, 0},  {1, 1},  {0, -2}, {1, -2} },
            {{0, 0}, {0, 0},  {0, 0},  {0, 0},  {0, 0}  },
            {{0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}}
        };

        std::vector<std::vector<std::pair<int, int>>> OWallKick = {
            {{0, 0}},
            {{0, 0}},
            {{0, 0}},
            {{0, 0}},
        };

        std::vector<std::vector<std::pair<int, int>>> IWallKick = {
            {{0, 0},   {-1, 0}, {2, 0},   {-1, 0}, {2, 0} },
            {{-1, 0},  {0, 0},  {0, 0},   {0, -1}, {0, 2} },
            {{-1, -1}, {1, -1}, {-2, -1}, {1, 0},  {-2, 0}},
            {{0, -1},  {0, -1}, {0, -1},  {0, 1},  {0, -2}}
        };

        switch (type)
        {
        case Tetris::TetrominoType::I:
            return Tetris::Tetromino(
                {
                    {{BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::BLK, BlockType::BLK, BlockType::BLK, BlockType::BLK},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL}},
                    {{BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::BLK, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::BLK, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::BLK, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::BLK, BlockType::NIL, BlockType::NIL}},
                    {{BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::BLK, BlockType::BLK, BlockType::BLK, BlockType::BLK, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL}},
                    {{BlockType::NIL, BlockType::NIL, BlockType::BLK, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::BLK, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::BLK, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::BLK, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL, BlockType::NIL}}
            },
                IWallKick,
                ftxui::Color::Cyan1,
                Tetris::TetrominoType::I
            );
        case Tetris::TetrominoType::O:
            return Tetris::Tetromino(
                {
                    {
                     {BlockType::BLK, BlockType::BLK},
                     {BlockType::BLK, BlockType::BLK},
                     },
                    {
                     {BlockType::BLK, BlockType::BLK},
                     {BlockType::BLK, BlockType::BLK},
                     },
                    {
                     {BlockType::BLK, BlockType::BLK},
                     {BlockType::BLK, BlockType::BLK},
                     },
                    {
                     {BlockType::BLK, BlockType::BLK},
                     {BlockType::BLK, BlockType::BLK},
                     }
            },
                OWallKick,
                ftxui::Color::Yellow1,
                Tetris::TetrominoType::O
            );
        case Tetris::TetrominoType::T:
            return Tetris::Tetromino(
                {
                    {{BlockType::NIL, BlockType::BLK, BlockType::NIL},
                     {BlockType::BLK, BlockType::BLK, BlockType::BLK},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL}},
                    {{BlockType::NIL, BlockType::BLK, BlockType::NIL},
                     {BlockType::NIL, BlockType::BLK, BlockType::BLK},
                     {BlockType::NIL, BlockType::BLK, BlockType::NIL}},
                    {{BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::BLK, BlockType::BLK, BlockType::BLK},
                     {BlockType::NIL, BlockType::BLK, BlockType::NIL}},
                    {{BlockType::NIL, BlockType::BLK, BlockType::NIL},
                     {BlockType::BLK, BlockType::BLK, BlockType::NIL},
                     {BlockType::NIL, BlockType::BLK, BlockType::NIL}}
            },
                JLTSZWallKick,
                ftxui::Color::MediumPurple1,
                Tetris::TetrominoType::T
            );
        case Tetris::TetrominoType::J:
            return Tetris::Tetromino(
                {
                    {{BlockType::BLK, BlockType::NIL, BlockType::NIL},
                     {BlockType::BLK, BlockType::BLK, BlockType::BLK},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL}},
                    {{BlockType::NIL, BlockType::BLK, BlockType::BLK},
                     {BlockType::NIL, BlockType::BLK, BlockType::NIL},
                     {BlockType::NIL, BlockType::BLK, BlockType::NIL}},
                    {{BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::BLK, BlockType::BLK, BlockType::BLK},
                     {BlockType::NIL, BlockType::NIL, BlockType::BLK}},
                    {{BlockType::NIL, BlockType::BLK, BlockType::NIL},
                     {BlockType::NIL, BlockType::BLK, BlockType::NIL},
                     {BlockType::BLK, BlockType::BLK, BlockType::NIL}}
            },
                JLTSZWallKick,
                ftxui::Color::Blue1,
                Tetris::TetrominoType::J
            );
        case Tetris::TetrominoType::L:
            return Tetris::Tetromino(
                {
                    {{BlockType::NIL, BlockType::NIL, BlockType::BLK},
                     {BlockType::BLK, BlockType::BLK, BlockType::BLK},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL}},
                    {{BlockType::NIL, BlockType::BLK, BlockType::NIL},
                     {BlockType::NIL, BlockType::BLK, BlockType::NIL},
                     {BlockType::NIL, BlockType::BLK, BlockType::BLK}},
                    {{BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::BLK, BlockType::BLK, BlockType::BLK},
                     {BlockType::BLK, BlockType::NIL, BlockType::NIL}},
                    {{BlockType::BLK, BlockType::BLK, BlockType::NIL},
                     {BlockType::NIL, BlockType::BLK, BlockType::NIL},
                     {BlockType::NIL, BlockType::BLK, BlockType::NIL}}
            },
                JLTSZWallKick,
                ftxui::Color::Orange1,
                Tetris::TetrominoType::L
            );
        case Tetris::TetrominoType::S:
            return Tetris::Tetromino(
                {
                    {{BlockType::NIL, BlockType::BLK, BlockType::BLK},
                     {BlockType::BLK, BlockType::BLK, BlockType::NIL},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL}},
                    {{BlockType::NIL, BlockType::BLK, BlockType::NIL},
                     {BlockType::NIL, BlockType::BLK, BlockType::BLK},
                     {BlockType::NIL, BlockType::NIL, BlockType::BLK}},
                    {{BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::NIL, BlockType::BLK, BlockType::BLK},
                     {BlockType::BLK, BlockType::BLK, BlockType::NIL}},
                    {{BlockType::BLK, BlockType::NIL, BlockType::NIL},
                     {BlockType::BLK, BlockType::BLK, BlockType::NIL},
                     {BlockType::NIL, BlockType::BLK, BlockType::NIL}}
            },
                JLTSZWallKick,
                ftxui::Color::Green1,
                Tetris::TetrominoType::S
            );
        case Tetris::TetrominoType::Z:
            return Tetris::Tetromino(
                {
                    {{BlockType::BLK, BlockType::BLK, BlockType::NIL},
                     {BlockType::NIL, BlockType::BLK, BlockType::BLK},
                     {BlockType::NIL, BlockType::NIL, BlockType::NIL}},
                    {{BlockType::NIL, BlockType::NIL, BlockType::BLK},
                     {BlockType::NIL, BlockType::BLK, BlockType::BLK},
                     {BlockType::NIL, BlockType::BLK, BlockType::NIL}},
                    {{BlockType::NIL, BlockType::NIL, BlockType::NIL},
                     {BlockType::BLK, BlockType::BLK, BlockType::NIL},
                     {BlockType::NIL, BlockType::BLK, BlockType::BLK}},
                    {{BlockType::NIL, BlockType::BLK, BlockType::NIL},
                     {BlockType::BLK, BlockType::BLK, BlockType::NIL},
                     {BlockType::BLK, BlockType::NIL, BlockType::NIL}}
            },
                JLTSZWallKick,
                ftxui::Color::Red1,
                Tetris::TetrominoType::Z
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