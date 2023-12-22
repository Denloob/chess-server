#include "Board.h"
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
            col++;

            if (type == Piece::Type::King)
            {
                if (color == Color::White)
                {
                    this->_white_king_pos = pos;
                }
                else
                {
                    this->_black_king_pos = pos;
                }
            }
        }
    }
}

Board::~Board() = default;
