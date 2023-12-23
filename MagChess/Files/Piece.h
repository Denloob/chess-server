#pragma once

#include "BoardConstants.h"
#include "Point.h"

class Board;
class Piece
{
  public:
    enum class Type : char
    {
        Pawn = 'p',
        King = 'k',
        Queen = 'q',
        Bishop = 'b',
        Knight = 'n',
        Rook = 'r',
    };
    enum class Color
    {
        Black,
        White,
    };
    using Attacks = BoardTable<bool>;

    Piece(Color color, const Point &pos, Board *board);
    Piece(const Piece &) = default;
    Piece &operator=(const Piece &) = default;
    virtual ~Piece() = default;

    virtual bool move_to(const Point &pos);
    virtual bool can_move_to(const Point &pos) const;
    virtual void add_attacks_to(Attacks &attacks) const = 0;

    Color color() const;
    Point pos() const;

    const Board *board() const;
    Board *board();

  protected:
    /**
     * @brief Check if move to the given pos would lead to a discovered attack
     *          on the king of the same color as the piece.
     *
     * @return Whether the move will lead to a discovered attack.
     */
    bool is_move_to_safe(const Point &pos) const;

  private:
    Color _color{};
    mutable Point _pos{};
    Board *_board;
};
