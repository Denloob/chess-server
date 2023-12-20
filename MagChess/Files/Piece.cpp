#include "Piece.h"

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

    Board copy_board = *_board;
    Piece *copy_this = copy_board[this->_pos];
    copy_board[copy_this->_pos] = nullptr;
    copy_board[pos] = copy_this;
    copy_this->_pos = pos;

    Attacks enemy_attacks{};
    for (const auto *piece : copy_board)
    {
        if (piece->color() != this->_color)
        {
            piece->add_attacks_to(enemy_attacks);
        }
    }

    Point king_pos = copy_board.king_of(this->_color).pos();

    return !enemy_attacks[king_pos.x][king_pos.y];
}

bool Piece::move_to(const Point &pos)
{
    if (!can_move_to(pos))
    {
        return false;
    }

    this->_board[this->_pos] = nullptr;
    this->_board[pos] = this;
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
