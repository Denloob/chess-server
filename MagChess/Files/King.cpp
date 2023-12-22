#include "King.h"
#include "Utils.h"

void King::add_attacks_to(Attacks& attacks) const
{
    Utils::add_nearby_places_attacks_to(attacks, *this);
}
