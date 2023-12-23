#include "Board.h"
#include "Pawn.h"
#include "Utils.h"

void Pawn::add_attacks_to(Attacks &attacks) const
{
    using namespace Utils::Direction;

    Utils::add_attacks_at_position_to(
        {
            up_direction() + RIGHT,
            up_direction() + LEFT,
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

    const auto up = up_direction();

    Point movement_direction = pos - this->pos();
    bool path_to_target_empty = (board.at(this->pos() + up) == nullptr &&
                                 board.at(this->pos() + up + up) == nullptr);

    return movement_direction == up + up && !has_moved() &&
           path_to_target_empty;
}

bool Pawn::can_advance_to(const Point &pos) const
{
    using namespace Utils::Direction;

    const Board &board = *this->board();

    const Piece *target = board.at(pos);
    bool target_empty = (target == nullptr);
    Point movement_direction = pos - this->pos();

    return movement_direction == up_direction() && target_empty;
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

Point Pawn::up_direction() const
{
    using namespace Utils::Direction;

    return color() == Color::White ? UP : DOWN;
}
