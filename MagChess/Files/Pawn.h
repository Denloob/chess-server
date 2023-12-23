#pragma once

#include "RestrictedPiece.h"

class Pawn : public RestrictedPiece
{
  public:
    using RestrictedPiece::RestrictedPiece;

    void add_attacks_to(Attacks &attacks) const override;
    bool can_move_to(const Point &pos) const override;

  private:
    bool can_advance_to(const Point &pos) const;
    bool can_double_dvance_to(const Point &pos) const;
    bool can_attack(const Point &pos) const;
    bool can_en_passant(const Point &pos) const;

    Type type() const override;
};
