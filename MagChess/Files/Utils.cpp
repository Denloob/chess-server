#include "Board.h"
#include "Piece.h"
#include "Point.h"
#include "Utils.h"
#include <initializer_list>
#include <stdexcept>

namespace
{
void add_attacks_in_direction_to(std::initializer_list<Point> directions,
                                 Piece::Attacks &attacks, const Piece &piece)
{
    const Board &board = *piece.board();
    for (auto direction : directions)
    {
        Point current_pos = piece.pos();
        bool hit_piece = false;

        try
        {
            while (!hit_piece)
            {
                current_pos += direction;

                hit_piece = board.at(current_pos) != nullptr;
                if (!hit_piece || board.at(current_pos)->color() != piece.color())
                {
                    attacks.at(current_pos.y).at(current_pos.x) = true;
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
void add_forks_attacks_to(Piece::Attacks &attacks, const Piece &piece)
{
    add_attacks_at_position_to(
        {Direction::UP + Direction::UP + Direction::LEFT,
         Direction::UP + Direction::UP + Direction::RIGHT,
         Direction::DOWN + Direction::DOWN + Direction::LEFT,
         Direction::DOWN + Direction::DOWN + Direction::RIGHT,
         Direction::RIGHT + Direction::RIGHT + Direction::UP,
         Direction::RIGHT + Direction::RIGHT + Direction::DOWN,
         Direction::LEFT + Direction::LEFT + Direction::UP,
         Direction::LEFT + Direction::LEFT + Direction::DOWN},
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
void add_nearby_places_attacks_to(Piece::Attacks &attacks, const Piece &piece)
{
    add_attacks_at_position_to(
        {
            Direction::LEFT,
            Direction::UP,
            Direction::DOWN,
            Direction::RIGHT,
            Direction::UP + Direction::RIGHT,
            Direction::UP + Direction::LEFT,
            Direction::DOWN + Direction::RIGHT,
            Direction::DOWN + Direction::LEFT,
        },
        attacks, piece);
}

void add_attacks_at_position_to(std::initializer_list<Point> positions,
                                Piece::Attacks &attacks, const Piece &piece)
{
    const Board &board = *piece.board();
    for (auto position : positions)
    {
        Point target_pos = piece.pos() + position;
        try
        {
            const Piece *target = board.at(target_pos);
            if (target == nullptr || target->color() != piece.color())
            {
                attacks.at(target_pos.y).at(target_pos.x) = true;
            }
        }
        catch (const std::out_of_range &)
        {
            // Ignore
        }
    }
}
} // namespace Utils
