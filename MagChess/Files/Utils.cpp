#include "Utils.h"
#include "Board.h"
#include "Piece.h"
#include "Point.h"
#include <initializer_list>
#include <stdexcept>

namespace
{
void add_attacks_in_direction_to(std::initializer_list<Point> directions,
                                 Piece::Attacks &attacks, const Piece &piece)
{
    const Board &board = *piece.board();//class piece has no member board
    for (auto direction : directions)
    {
        Point current_pos = piece.pos();
        bool hit_piece = false;

        try
        {
            while (!hit_piece)
            {
                current_pos += direction;

                hit_piece = board[current_pos] != nullptr;
                if (hit_piece && board[current_pos]->color() != piece.color())
                {
                    attacks[current_pos.x][current_pos.y] = true;
                }
            }
        }
        catch (const std::out_of_range &)
        {
            // Ignore
        }
    }
}
} // namespace

namespace Utils
{
void add_orthogonal_attacks_to(Piece::Attacks &attacks, const Piece &piece)
{
    add_attacks_in_direction_to(
        {Direction::LEFT, Direction::RIGHT, Direction::UP, Direction::DOWN},
        attacks, piece);
}

void add_diagonal_attacks_to(Piece::Attacks &attacks, const Piece &piece)
{
    add_attacks_in_direction_to(
        {Direction::LEFT + Direction::UP, Direction::RIGHT + Direction::UP,
         Direction::LEFT + Direction::DOWN, Direction::RIGHT + Direction::DOWN},
        attacks, piece);
}
void add_forks_attacks_to(Piece::Attacks& attacks, const Piece& piece)
{
    add_attacks_in_direction_to(
        {
            Direction::UP + Direction::UP + Direction::LEFT , 
            Direction::UP + Direction::UP + Direction::RIGHT,
            Direction::DOWN + Direction::DOWN + Direction::LEFT,
            Direction::DOWN + Direction::DOWN + Direction::RIGHT,
            Direction::RIGHT + Direction::RIGHT + Direction::UP,
            Direction::RIGHT + Direction::RIGHT + Direction::DOWN,
            Direction::LEFT + Direction::LEFT + Direction::UP,
            Direction::LEFT + Direction::LEFT + Direction::DOWN
        },
        /*
           | ||*| |*|| |
           ------------
           |*|| | | ||*|
           ------------
           | || |K| || |
           ------------
           |*|| | | ||*|
           ------------
           | ||*| |*|| |
        */
        attacks, piece);
}
void add_nearby_places_attacks_to(Piece::Attacks& attacks, const Piece& piece)
{
    add_attacks_in_direction_to(
        { Direction::LEFT , Direction::UP , Direction::DOWN,Direction::RIGHT,
          Direction::UP + Direction::RIGHT , Direction::UP + Direction::LEFT,
          Direction::DOWN + Direction::RIGHT , Direction::DOWN + Direction::LEFT,
        },
        attacks, piece);
}
void add_above_row_attacks_to(Piece::Attacks& attacks, const Piece& piece)
{
    add_attacks_in_direction_to(
        {
          Direction::UP + Direction::RIGHT , Direction::UP + Direction::LEFT,Direction::UP,
        },
        attacks, piece);
}
} // namespace Utils
