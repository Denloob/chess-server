#pragma once

#include "Piece.h"
#include "Point.h"

class RestrictedPiece : public Piece
{
  public:
    RestrictedPiece(Color color, const Point &pos);
    ~RestrictedPiece() override = default;

    /**
     * @brief Moves the piece to the given point.
     *
     * @param point The point to move the piece to.
     * @return Whether the move was successful.
     */
    bool move_to(const Point &point) override;

  protected:
    /**
     * @brief Checks if the piece has moved.
     *
     * @return Whether the piece has moved.
     */
    bool has_moved() const;

  private:
    bool _moved = false;
};
