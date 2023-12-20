#include "RestrictedPiece.h"

RestrictedPiece::RestrictedPiece(Color color, const Point &pos)
    : Piece(color, pos)
{
}

bool RestrictedPiece::move_to(const Point &point)
{
    _moved = true;

    return Piece::move_to(point);
}

bool RestrictedPiece::has_moved() const
{
    return _moved;
}
