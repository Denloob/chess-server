#include "Piece.h"
#include "Board.h"
#include <memory>

Piece::Piece(Color color, const Point &pos, Board *board) : _color(color), _pos(pos), _board(board)
{
}

bool Piece::is_move_to_safe(const Point &pos) const
{
    Board &board = *this->_board;

    std::unique_ptr<Piece> prev_piece = std::move(board[pos]);
    Point prev_pos = this->_pos;

    board[pos] = std::move(board[this->_pos]);
    this->_pos = pos;

    bool can_move = !board.under_check(color());

    this->_pos = prev_pos;
    board[prev_pos] = std::move(board[pos]);
    board[pos] = std::move(prev_piece);

    return can_move;
}

bool Piece::can_move_to(const Point &pos) const
{
    Attacks attacks{};
    add_attacks_to(attacks);

    return attacks.at(pos.x).at(pos.y) && is_move_to_safe(pos);
}

bool Piece::move_to(const Point &pos)
{
    if (!can_move_to(pos))
    {
        return false;
    }

    Board &board = *this->_board;

    board[pos] = std::move(board[this->_pos]);
    this->_pos = pos;

    return true;
}

Piece::Color Piece::color() const
{
    return this->_color;
}

Point Piece::pos() const
{
    return this->_pos;
}

const Board *Piece::board() const
{
    return this->_board;
}

Board *Piece::board()
{
    return this->_board;
}
