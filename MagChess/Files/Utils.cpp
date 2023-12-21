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
} // namespace Utils