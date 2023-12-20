#pragma once

#include "Board.h"
#include "Point.h"

class Piece
{
  public:
    enum class Color
    {
        Black,
        White,
    };
    using Attacks = BoardTable<bool>;

    Piece(Color color, const Point &pos);
    Piece(const Piece &) = default;
    Piece &operator=(const Piece &) = default;
    virtual ~Piece() = default;

    virtual bool move_to(const Point &pos);
    virtual bool can_move_to(const Point &pos) const = 0;
    virtual void add_attacks_to(Attacks &attacks) const = 0;

    Color color() const;
    Point pos() const;

  private:
    Point _pos{};
    Color _color{};
};
