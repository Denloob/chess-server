#pragma once

#include "Piece.h"

class Knight : public Piece
{
    using Piece::can_move_to;
    using Piece::Piece;

    void add_attacks_to(Attacks& attacks) const override;

    Type type() const override;
};
