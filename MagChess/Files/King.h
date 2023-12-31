#pragma once

#include "RestrictedPiece.h"

class King : public RestrictedPiece
{
    using RestrictedPiece::check_move_to;
    using RestrictedPiece::RestrictedPiece;

    void add_attacks_to(Attacks& attacks) const override;
    bool can_castle(Point direction) const;
    Type type() const override;
};
