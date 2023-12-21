#include "Board.h"

Board::Board(const std::string &build_format_string) 
{
    this->_black_king_pos = nullptr;
    this->_white_king_pos = nullptr;
    size_t row = 0;
    size_t col = 0;

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
                _board[row][col++] = std::make_unique<Piece>(Piece::Color::white, new Point()); // Replace with actual Pawn class
                break;
            case 'P':
                _board[row][col++] = std::make_unique<Piece>(); // Replace with actual Pawn class
                break;
            case 'k':
                _board[row][col++] = std::make_unique<King>();
                break;
            case 'K':
                _board[row][col++] = std::make_unique<King>();
                break;
            case 'q':
                _board[row][col++] = std::make_unique<Piece>(); 
                break;
            case 'Q':
                _board[row][col++] = std::make_unique<Piece>();
                break;
            case 'b':
                _board[row][col++] = std::make_unique<Piece>(); 
                break;
            case 'B':
                _board[row][col++] = std::make_unique<Piece>(); 
                break;
            case 'n':
                _board[row][col++] = std::make_unique<Piece>(); 
                break;
            case 'N':
                _board[row][col++] = std::make_unique<Piece>(); 
                break;
            case 'r':
                _board[row][col++] = std::make_unique<Piece>(); 
                break;
            case 'R':
                _board[row][col++] = std::make_unique<Piece>(); 
                break;
            default:
                _board[row][col++] = nullptr;
            }
        }
    }
}