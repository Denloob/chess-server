#include "RestrictedPiece.h"

bool RestrictedPiece::move_to(const Point &point)
{
    bool success = Piece::move_to(point);

    if (!_moved && success)
    {
        _moved = true;
    }

    return success;
}

bool RestrictedPiece::has_moved() const
{
    return _moved;
}
