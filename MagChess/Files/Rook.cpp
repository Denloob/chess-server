#include "Rook.h"
#include "Utils.h"

void Rook::add_attacks_to(Attacks &attacks) const
{
    Utils::add_orthogonal_attacks_to(attacks, *this);
}

Piece::Type Rook::type() const
{
    return Type::Rook;
}
