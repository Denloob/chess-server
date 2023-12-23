#include "Queen.h"
#include "Utils.h"

void Queen::add_attacks_to(Attacks &attacks) const
{
    Utils::add_diagonal_attacks_to(attacks, *this);
    Utils::add_orthogonal_attacks_to(attacks, *this);
}

Piece::Type Queen::type() const
{
    return Type::Queen;
}
