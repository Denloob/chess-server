#pragma once

#include "RestrictedPiece.h"

class Pawn : public RestrictedPiece
{
    using RestrictedPiece::can_move_to;
    using RestrictedPiece::RestrictedPiece;

    void add_attacks_to(Attacks& attacks) const override;
};
