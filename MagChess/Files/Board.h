#pragma once
#include "Point.h"
#include <iostream>
#include <array>
#include <memory>
#define DEFAULT_BOARD_STRING "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq"
constexpr int BOARD_SIZE = 8;
template <typename T>
using BoardTable = std::array<std::array<T, BOARD_SIZE>, BOARD_SIZE>;

class Piece;
class Board
{
public:
    Board(const std::string &build_format_string = DEFAULT_BOARD_STRING);

    Board(const Board &) = delete;
    Board(Board &&) = delete;
    Board &operator=(const Board &) = delete;
    Board &operator=(Board &&) = delete;

    ~Board();
     //std::string to_string(); decide later

private:
    Point _black_king_pos;
    Point _white_king_pos;
    BoardTable <std::unique_ptr<Piece>> _board{};
};
