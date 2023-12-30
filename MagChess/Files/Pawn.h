#pragma once

#include "RestrictedPiece.h"

class Pawn : public RestrictedPiece
{
  public:
    using RestrictedPiece::RestrictedPiece;

    void add_attacks_to(Attacks &attacks) const override;
    void check_move_to(const Point &pos) const noexcept(false) override;

  private:
    bool can_advance_to(const Point &pos) const;
    bool can_double_dvance_to(const Point &pos) const;
    bool can_attack(const Point &pos) const;
    bool can_en_passant(const Point &pos) const;
    bool can_move() const override;
    Point up_direction() const;

    Type type() const override;
};
