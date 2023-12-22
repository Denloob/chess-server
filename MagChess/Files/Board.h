#pragma once
#include "Point.h"
#include <iostream>
#include <array>
#include <memory>
#define DEFAULT_BOARD_STRING "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq"
constexpr int BOARD_SIZE = 7; //8 lines index 0 -7
template <typename T>
using BoardTable = std::array<std::array<T, BOARD_SIZE>, BOARD_SIZE>;

#include "Piece.h"
#include "Bishop.h"
#include "Queen.h"
#include "Rook.h"
#include "King.h"
#include "Knight.h"

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
    Board(const std::string &build_format_string = DEFAULT_BOARD_STRING);
    ~Board() = default;
     //std::string to_string(); 

private:
    Point _black_king_pos;
    Point _white_king_pos;
    BoardTable <std::unique_ptr<Piece>> _board{};
};
