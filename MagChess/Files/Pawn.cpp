#include "Board.h"
#include "Pawn.h"
#include "Utils.h"

void Pawn::add_attacks_to(Attacks &attacks) const
{
    using namespace Utils::Direction;

    Utils::add_attacks_at_position_to(
        {
            UP + RIGHT,
            UP + LEFT,
        },
        attacks, *this);
}

bool Pawn::can_move_to(const Point &pos) const
{
    return is_move_to_safe(pos) &&
           (can_advance_to(pos) || can_double_dvance_to(pos) ||
            can_attack(pos));
}

bool Pawn::can_double_dvance_to(const Point &pos) const
{
    using namespace Utils::Direction;

    const Board &board = *this->board();

    Point movement_direction = pos - this->pos();
    bool path_to_target_empty = (board.at(this->pos() + UP) == nullptr &&
                                 board.at(this->pos() + UP + UP) == nullptr);

    return movement_direction == UP + UP && !has_moved() &&
           path_to_target_empty;
}

bool Pawn::can_advance_to(const Point &pos) const
{
    using namespace Utils::Direction;

    const Board &board = *this->board();

    const Piece *target = board.at(pos);
    bool target_empty = (target == nullptr);
    Point movement_direction = pos - this->pos();

    return movement_direction == UP && target_empty;
}

bool Pawn::can_attack(const Point &pos) const
{
    const Board &board = *this->board();

    const Piece *target = board.at(pos);
    bool target_empty = (target == nullptr);

    Attacks attacks{};
    add_attacks_to(attacks);

    return attacks.at(pos.x).at(pos.y) && !target_empty &&
           target->color() != this->color();
}

Piece::Type Pawn::type() const
{
    return Type::Pawn;
}
