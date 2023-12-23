#include "Board.h"
#include "King.h"
#include "Piece.h"
#include "PieceFactory.h"
#include <cctype>

Board::Board(const std::string &build_format_string)
{
    int row = 0;
    int col = 0;

    for (char c : build_format_string)
    {
        if (c == ' ')
            break;

        if (c == '/')
        {
            row++;
            col = 0;
        }
        else if (isdigit(c))
        {
            int emptyCount = c - '0';
            for (int i = 0; i < emptyCount; ++i)
            {
                _board[row][col] = nullptr;
                col++;
            }
        }
        else
        {
            using Color = Piece::Color;

            auto type = static_cast<Piece::Type>(std::tolower(c));
            auto color = std::isupper(c) ? Color::White : Color::Black;
            Point pos{row, col};

            _board[row][col] = PieceFactory::create_shape(type, color, pos);

            if (type == Piece::Type::King)
            {
                auto *king = dynamic_cast<King *>(_board[row][col].get());
                king_ptr_of(color) = king;
            }

            col++;
        }
    }
}

Board::~Board() = default;

const Piece *Board::at(const Point &pos) const
{
    return _board[pos.x][pos.y].get();
}

Piece *Board::at(const Point &pos)
{
    return _board[pos.x][pos.y].get();
}

std::unique_ptr<Piece> &Board::operator[](const Point &pos)
{
    return _board[pos.x][pos.y];
}

const King &Board::king_of(Piece::Color color) const
{
    return *king_ptr_of(color);
}

King &Board::king_of(Piece::Color color)
{
    return *king_ptr_of(color);
}

const King *const &Board::king_ptr_of(Piece::Color color) const
{
    return color == Piece::Color::White ? _white_king : _black_king;
}

King *&Board::king_ptr_of(Piece::Color color)
{
    return color == Piece::Color::White ? _white_king : _black_king;
}
