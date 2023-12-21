#pragma once

#include "Piece.h"

class Bishop : public Piece
{
    using Piece::can_move_to;
    using Piece::Piece;

    void add_attacks_to(Attacks &attacks) const override;
};
