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

void Piece::check_move_to(const Point &pos) const
{
    if (!is_move_to_safe(pos))
    {
        throw PieceException{Client::MoveResult::CheckOnSelf};
    }

    if (pos == this->pos())
    {
        throw PieceException{Client::MoveResult::MoveToSelf};
    }

    if (board()->at(pos) != nullptr && board()->at(pos)->color() == color())
    {
        throw PieceException{Client::MoveResult::DestinationOccupied};
    }


    Attacks attacks{};
    add_attacks_to(attacks);

    if (!attacks.at(pos.y).at(pos.x))
    {
        throw PieceException{Client::MoveResult::IllegalDestination};
    }
}

bool Piece::can_move() const
{
    Attacks attacks{};
    add_attacks_to(attacks);
    for (int y = 0; y <= BOARD_SIZE; y++)
    {
        for (int x = 0; x <= BOARD_SIZE; x++)
        {
            const Point pos{ x, y };
            if (attacks.at(pos.y).at(pos.x))
            {
                if (this->is_move_to_safe(pos))
                {
                    return true;
                }
            }
        }
    }
    return false;
}
bool Piece::move_to(const Point &pos)
{
    check_move_to(pos);

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

PieceException::PieceException(Client::MoveResult reason) : _reason{reason}
{
}

Client::MoveResult PieceException::reason() const noexcept
{
    return _reason;
}
