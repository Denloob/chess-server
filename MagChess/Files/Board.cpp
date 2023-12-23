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
                _board.at(row).at(col) = nullptr;
                col++;
            }
        }
        else
        {
            using Color = Piece::Color;

            auto type = static_cast<Piece::Type>(std::tolower(c));
            auto color = std::isupper(c) ? Color::White : Color::Black;
            Point pos{row, col};

            _board.at(row).at(col) = PieceFactory::create_shape(type, color, pos);

            if (type == Piece::Type::King)
            {
                auto *king = dynamic_cast<King *>(_board.at(row).at(col).get());
                king_ptr_of(color) = king;
            }

            col++;
        }
    }
}

Board::~Board() = default;

const Piece *Board::at(const Point &pos) const
{
    return _board.at(pos.x).at(pos.y).get();
}

Piece *Board::at(const Point &pos)
{
    return _board.at(pos.x).at(pos.y).get();
}

std::unique_ptr<Piece> &Board::operator[](const Point &pos)
{
    return _board.at(pos.x).at(pos.y);
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

bool Board::under_check(Piece::Color color)
{
    Piece::Attacks enemy_attacks{};
    for (const auto &row : _board)
    {
        for (const auto &piece : row)
        {
            if (piece.get() != nullptr && piece->color() != color)
            {
                piece->add_attacks_to(enemy_attacks);
            }
        }
    }

    Point king_pos = king_of(color).pos();

    return enemy_attacks.at(king_pos.x).at(king_pos.y);
}
