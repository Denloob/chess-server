#pragma once

#include "Piece.h"
#include "Point.h"
#include <initializer_list>

namespace Utils
{
namespace Direction
{
constexpr Point LEFT{-1, 0};
constexpr Point RIGHT{1, 0};
constexpr Point UP{0, -1};
constexpr Point DOWN{0, 1};
} // namespace Direction

void add_orthogonal_attacks_to(Piece::Attacks &attacks, const Piece &piece);
void add_diagonal_attacks_to(Piece::Attacks &attacks, const Piece &piece);
void add_attacks_at_position_to(std::initializer_list<Point> positions,
                                Piece::Attacks &attacks, const Piece &piece);

void add_forks_attacks_to(Piece::Attacks& attacks, const Piece& piece);
void add_nearby_places_attacks_to(Piece::Attacks& attacks, const Piece& piece);
void add_above_row_attacks_to(Piece::Attacks& attacks, const Piece& piece);
} // namespace Utils
