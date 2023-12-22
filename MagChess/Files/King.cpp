#include "Rook.h"
#include "Utils.h"

void Rook::add_attacks_to(Attacks& attacks) const
{
    Utils::add_nearby_places_attacks_to(attacks, *this);
}
