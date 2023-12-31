#include "Board.h"
#include "King.h"
#include "Rook.h"
#include "Utils.h"
#include <algorithm>
#include <cassert>
#include <vector>
//THE KING

#define RIGHT_CASTLE_DELTA (Utils::Direction::RIGHT + Utils::Direction::RIGHT)
#define LEFT_CASTLE_DELTA (Utils::Direction::LEFT + Utils::Direction::LEFT)

void King::add_attacks_to(Attacks &attacks) const
{
    Utils::add_nearby_places_attacks_to(attacks, *this);
}

Piece::Type King::type() const
{
    return Type::King;
}

bool King::move_to(const Point &pos)
{
    Board &board = *this->board();

    Point movement_delta = pos - this->pos();
    bool is_castle = is_move_castle(pos);

    RestrictedPiece::move_to(pos);

    if (is_castle)
    {
        const Point castle_direction = get_castle_direction(movement_delta);
        Point rook_pos = this->pos() + castle_direction;
        if (castle_direction == Utils::Direction::LEFT)
        {
            rook_pos += castle_direction;
        }

        const Point new_rook_pos = this->pos() - castle_direction;
        board[new_rook_pos] = std::move(board[rook_pos]);
        board.at(new_rook_pos)->pos() = new_rook_pos;
    }

    return true;
}

bool King::can_castle(const Point &direction) const
{
    using namespace Utils::Direction;
    assert(direction == RIGHT || direction == LEFT);

    const Board &curr_board = *this->board();
    Point king_pos = this->pos();

    if (this->has_moved() || curr_board.under_check(this->color()))
    {
        return false;
    }

    std::vector<Point> king_path = {king_pos + direction,
                                    king_pos + direction + direction};
    if (!std::all_of(std::begin(king_path), std::end(king_path),
                     [this](const Point &pos) {
                         return this->is_move_to_safe(pos) &&
                                this->board()->at(pos) == nullptr;
                     }))
    {

        return false;
    }

    Point rook_pos = king_path.back() + direction;

    if (direction == LEFT)
    {
        const Point &rook_path = rook_pos;
        if (curr_board.at(rook_path) != nullptr)
        {
            return false;
        }

        rook_pos = rook_path + direction;
    }

    const Piece *rook_pos_piece = curr_board.at(rook_pos);
    if (rook_pos_piece == nullptr ||
        rook_pos_piece->type() != Piece::Type::Rook)
    {
        return false;
    }

    const auto *rook = dynamic_cast<const Rook *>(rook_pos_piece);

    return !rook->has_moved();
}

bool King::is_move_castle(const Point &pos) const
{
    if (has_moved())
    {
        return false;
    }

    const Point move_delta = pos - this->pos();
    return move_delta == RIGHT_CASTLE_DELTA || move_delta == LEFT_CASTLE_DELTA;
}

Point King::get_castle_direction(const Point &movement_delta)
{
    using namespace Utils::Direction;
    return movement_delta == RIGHT_CASTLE_DELTA ? RIGHT : LEFT;
}

void King::check_move_to(const Point &pos) const
{
    if (is_move_castle(pos) &&
        can_castle(get_castle_direction(pos - this->pos())))
    {
        return;
    }

    Piece::check_move_to(pos);
}
