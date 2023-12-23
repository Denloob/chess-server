#pragma once

#include "Piece.h"
#include <memory>
#include <stdexcept>
#include <utility>
#include "Bishop.h"
#include "Queen.h"
#include "Rook.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"

namespace PieceFactory
{
template <typename... Args>
std::unique_ptr<Piece> create_shape(Piece::Type type, Args &&...args)
{
    switch (type)
    {
        case Piece::Type::Pawn:
            return std::make_unique<Pawn>(std::forward<Args>(args)...);
            break;
        case Piece::Type::King:
            return std::make_unique<King>(std::forward<Args>(args)...);
            break;
        case Piece::Type::Queen:
            return std::make_unique<Queen>(std::forward<Args>(args)...);
            break;
        case Piece::Type::Bishop:
            return std::make_unique<Bishop>(std::forward<Args>(args)...);
            break;
        case Piece::Type::Knight:
            return std::make_unique<Knight>(std::forward<Args>(args)...);
            break;
        case Piece::Type::Rook:
            return std::make_unique<Rook>(std::forward<Args>(args)...);
            break;
        default:
            throw std::invalid_argument("Invalid piece type");
    }
}
} // namespace PieceFactory
