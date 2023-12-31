#pragma once

#include "Piece.h"

class Bishop : public Piece
{
  public:
    using Piece::check_move_to;
    using Piece::Piece;

    void add_attacks_to(Attacks &attacks) const override;

    Type type() const override;
};
