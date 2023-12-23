#include "Knight.h"
#include "Utils.h"

void Knight::add_attacks_to(Attacks& attacks) const
{
    Utils::add_forks_attacks_to(attacks, *this);
}

Piece::Type Knight::type() const
{
    return Type::Knight;
}
