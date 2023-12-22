#include "Board.h"

Board::Board(const std::string& build_format_string = DEFAULT_BOARD_STRING)
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
                _board[row][col++] = nullptr;
            }
        }
        else
        {
            switch (c)
            {
                //(upper = white, lower = black)
            case 'p':
                _board[row][col++] = std::make_unique<Pawn>(Piece::Color::Black, Point{ row,col });
                break;
            case 'P':
                _board[row][col++] = std::make_unique<Pawn>(Piece::Color::White , Point{ row,col });                break;
            case 'k':
                _board[row][col++] = std::make_unique<King>(Piece::Color::Black, Point{ row,col });
                this->_black_king_pos = Point{row,col};
                break;
            case 'K':
                _board[row][col++] = std::make_unique<King>(Piece::Color::White, Point{ row,col });
                this->_white_king_pos = Point{ row,col };
                break;
            case 'q':
                _board[row][col++] = std::make_unique<Queen>(Piece::Color::Black, Point{ row,col });
                break;
            case 'Q':
                _board[row][col++] = std::make_unique<Queen>(Piece::Color::White, Point{ row,col });
                break;
            case 'b':
                _board[row][col++] = std::make_unique<Bishop>(Piece::Color::Black, Point{ row,col });
                break;
            case 'B':
                _board[row][col++] = std::make_unique<Bishop>(Piece::Color::White, Point{ row,col });
                break;
            case 'n':
                _board[row][col++] = std::make_unique<Knight>(Piece::Color::Black, Point{ row,col });
                break;
            case 'N':
                _board[row][col++] = std::make_unique<Knight>(Piece::Color::White, Point{ row,col });
                break;
            case 'r':
                _board[row][col++] = std::make_unique<Rook>(Piece::Color::Black, Point{ row,col });
                break;
            case 'R':
                _board[row][col++] = std::make_unique<Rook>(Piece::Color::White, Point{ row,col });
                break;
            default:
                _board[row][col++] = nullptr;
            }
        }
    }
}
