#pragma once
#include "Point.h"
#include <iostream>
#include <array>
#include "Piece.h"
#include <memory>
constexpr int BOARD_SIZE = 8;
template <typename T>
using BoardTable = std::array<std::array<T, BOARD_SIZE>, BOARD_SIZE>;

class Board
{

enum class Type : char
    {
        Pawn = 'p',
        King = 'k',
        Queen = 'q',
        Bishop = 'b',
        Knight = 'n',
        Rook = 'r',
    };

public:
    Board(const std::string &build_format_string) ;
    ~Board() = default;
     std::string to_string();

private:
    King* _black_king_pos;
    King* _white_king_pos;
    BoardTable <std::unique_ptr<Piece>> _board{};
};