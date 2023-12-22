#include "Pawn.h"
#include "Utils.h"

void Pawn::add_attacks_to(Attacks& attacks) const
{
    Utils::add_above_row_attacks_to(attacks, *this);
}
