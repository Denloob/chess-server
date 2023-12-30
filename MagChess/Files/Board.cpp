#include "Board.h"
#include "King.h"
#include "Piece.h"
#include "PieceFactory.h"
#include <cctype>

Board::Board(const std::string &build_format_string)
{
    Point pos{0, 0};

    for (char c : build_format_string)
    {
        if (c == ' ')
            break;

        if (c == '/')
        {
            pos.y++;
            pos.x = 0;
        }
        else if (isdigit(c))
        {
            int emptyCount = c - '0';
            for (int i = 0; i < emptyCount; ++i)
            {
                (*this)[pos] = nullptr;
                pos.x++;
            }
        }
        else
        {
            using Color = Piece::Color;

            auto type = static_cast<Piece::Type>(std::tolower(c));
            auto color = std::isupper(c) ? Color::White : Color::Black;

            (*this)[pos] = PieceFactory::create_piece(type, color, pos, this);

            if (type == Piece::Type::King)
            {
                auto *king = dynamic_cast<King *>(this->at(pos));
                king_ptr_of(color) = king;
            }

            pos.x++;
        }
    }
}

Board::~Board() = default;

const Piece *Board::at(const Point &pos) const
{
    return _board.at(pos.y).at(pos.x).get();
}

Piece *Board::at(const Point &pos)
{
    return _board.at(pos.y).at(pos.x).get();
}

std::unique_ptr<Piece> &Board::operator[](const Point &pos)
{
    return _board.at(pos.y).at(pos.x);
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
std::string Board::to_fed_string(const Board& board) const
{
    std::string result;

    for (int y = 0; y <= BOARD_SIZE; y++)
    {
        int emptyCount = 0;

        for (int x = 0; x <= BOARD_SIZE; x++)
        {
            const Point pos{ x, y };
            const Piece* piece = board.at(pos);
            if (!piece)
            {
                emptyCount++;
            }
            else
            {
                if (emptyCount > 0)
                {
                    result += std::to_string(emptyCount);
                    emptyCount = 0;
                }

                char pieceChar = (piece->color() == Piece::Color::White) ? std::toupper(static_cast<char>(piece->type())) : static_cast<char>(piece->type());
                result += pieceChar;
            }
        }

        if (emptyCount > 0)
        {
            result += std::to_string(emptyCount);
        }

        if (y < BOARD_SIZE)
        {
            result += "/";
        }
    }

    return result;
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

    return enemy_attacks.at(king_pos.y).at(king_pos.x);
}

bool Board::under_mate(Piece::Color color)
{
    for (int y = 0; y <= BOARD_SIZE; y++)
    {
        for (int x = 0; x <= BOARD_SIZE; x++)
        {
            const Point pos{ x, y };
            const Piece* piece = this->at(pos);
            if (piece != nullptr && piece->can_move())
            {
                return false; //not mate
            }
        }
    }
    return true; //mate
}
std::string Board::to_string() const
{
    std::string res;
    for (const auto &row : _board)
    {
        for (const auto &piece : row)
        {
            if (piece.get() == nullptr)
            {
                res += '#';
            }
            else
            {
                const auto piece_char = static_cast<char>(piece->type());
                res += piece->color() == Piece::Color::White
                           ? std::toupper(piece_char)
                           : std::tolower(piece_char);
            }
        }
    }

    return res;
}

namespace
{
Piece::Color next_color(Piece::Color color)
{
    switch (color)
    {
        case Piece::Color::Black:
            return Piece::Color::White;
        case Piece::Color::White:
            return Piece::Color::Black;
    }
}
} // namespace

Client::MoveResult Board::do_move(Client::Move move)
{
    using MoveResult = Client::MoveResult;

    try
    {
        Piece *piece = this->at(move.source);
        if (piece == nullptr || piece->color() != _current_color)
        {
            return MoveResult::NotYourPiece;
        }

        piece->move_to(move.dest);

        _current_color = next_color(_current_color);
        return this->under_check(_current_color) ? (this->under_mate(_current_color) ? MoveResult::CheckMate : MoveResult::Check)  : MoveResult::Ok;
    }
    catch (std::out_of_range &)
    {
        return MoveResult::NonExistentSquare;
    }
    catch (PieceException &e)
    {
        return e.reason();
    }
}
