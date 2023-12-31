#include "King.h"
#include "Utils.h"
#include "Board.h"
//THE KING
void King::add_attacks_to(Attacks& attacks) const
{
    Utils::add_nearby_places_attacks_to(attacks, *this);
}

Piece::Type King::type() const
{
    return Type::King;
}
bool King::can_castle(Point direction) const
{
    const Board& curr_board = *this->board();
    Point king_pos = this->pos();
    bool king_moved = this->has_moved();
    if (curr_board.at(king_pos + direction) == nullptr && curr_board.at(king_pos + direction + direction) == nullptr && !king_moved &&
        this->is_move_to_safe(king_pos + direction) && this->is_move_to_safe(king_pos + direction + direction))
    {
        Point rock_pos;
        if (direction.x == -1 && curr_board.at(king_pos+direction+direction+direction) == nullptr && this->is_move_to_safe(king_pos + direction + direction + direction))
        {
            //left direction
            rock_pos = king_pos + direction + direction + direction;
            //TO DO check if the piece is rock and his has_moved is false if so return true
        }
        else
        {
            //right direction
            rock_pos = king_pos + direction + direction;
            //TO DO check if the piece is rock and his has_moved is false if so return true
        }
    }
    return false;
}