#include "Piece.h"
#include "Board.h"
#include <memory>

Piece::Piece(Color color, const Point &pos) : _color(color), _pos(pos)
{
}

Point get_king(const Board &board)
{
    for (const auto *piece : board)
    {
        if (piece->get_type() == Piece::Type::King)
        {
            return piece->pos();
        }
    }
}

bool Piece::can_move_to(const Point &pos) const
{
    Attacks attacks{};
    add_attacks_to(attacks);

    if (!attacks[pos.x][pos.y])
    {
        return false;
    }

    std::unique_ptr<Piece> prev_piece = std::move(_board[pos]);
    Point prev_pos = this->_pos;

    _board[pos] = std::move(_board[this->_pos]);
    this->_pos = pos;

    Attacks enemy_attacks{};
    for (const auto *piece : _board)
    {
        if (piece->color() != this->_color)
        {
            piece->add_attacks_to(enemy_attacks);
        }
    }

    Point king_pos = _board.king_of(this->_color).pos();

    bool can_move = !enemy_attacks[king_pos.x][king_pos.y];
    this->_pos = prev_pos;
    _board[prev_pos] = std::move(_board[pos]);
    _board[pos] = std::move(prev_piece);

    return can_move;
}

bool Piece::move_to(const Point &pos)
{
    if (!can_move_to(pos))
    {
        return false;
    }

    this->_board[pos] = std::move(this->_board[this->_pos]);
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
