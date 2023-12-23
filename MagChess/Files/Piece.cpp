#include "Piece.h"
#include "Board.h"
#include <memory>

Piece::Piece(Color color, const Point &pos, Board *board) : _color(color), _pos(pos), _board(board)
{
}

bool Piece::can_move_to(const Point &pos) const
{
    Attacks attacks{};
    add_attacks_to(attacks);

    if (!attacks.at(pos.x).at(pos.y))
    {
        return false;
    }

    Board &board = *this->_board;

    std::unique_ptr<Piece> prev_piece = std::move(board[pos]);
    Point prev_pos = this->_pos;

    board[pos] = std::move(board[this->_pos]);
    this->_pos = pos;

    Attacks enemy_attacks{};
    for (const auto *piece : board)
    {
        if (piece->color() != this->_color)
        {
            piece->add_attacks_to(enemy_attacks);
        }
    }

    Point king_pos = board.king_of(this->_color).pos();

    bool can_move = !enemy_attacks.at(king_pos.x).at(king_pos.y);
    this->_pos = prev_pos;
    board[prev_pos] = std::move(board[pos]);
    board[pos] = std::move(prev_piece);

    return can_move;
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
