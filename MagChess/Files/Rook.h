#pragma once

#include "RestrictedPiece.h"

class Rook : public RestrictedPiece
{
    using RestrictedPiece::can_move_to;
    using RestrictedPiece::RestrictedPiece;

    void add_attacks_to(Attacks &attacks) const override;

    Type type() const override;
};
