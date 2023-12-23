#include "Bishop.h"
#include "Utils.h"

void Bishop::add_attacks_to(Attacks &attacks) const
{
    Utils::add_diagonal_attacks_to(attacks, *this);
}

Piece::Type Bishop::type() const
{
    return Type::Bishop;
}
