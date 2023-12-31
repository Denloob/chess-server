#pragma once

#include "RestrictedPiece.h"

class King : public RestrictedPiece
{
  public:
    using RestrictedPiece::check_move_to;
    using RestrictedPiece::RestrictedPiece;

    void add_attacks_to(Attacks &attacks) const override;
    void check_move_to(const Point &pos) const noexcept(false) override;
    bool move_to(const Point &pos) override;
    Type type() const override;

  private:
    bool can_castle(const Point &direction) const;
    bool is_move_castle(const Point &pos) const;
    static Point get_castle_direction(const Point &movement_delta);
};
