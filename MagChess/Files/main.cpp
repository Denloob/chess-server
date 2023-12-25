#include "Board.h"
#include "Client.h"
#include "MagshimimUi.h"
#include "Piece.h"
#include <string>

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

int main()
{
    using MoveResult = Client::MoveResult;

    Board b;
    MagshimimUI ui{&b};
    Piece::Color current_color = Piece::Color::White;

    while (true)
    {
        Client::Move move = ui.receive();

        MoveResult result{};
        try
        {
            Piece *piece = b.at(move.source);
            if (piece != nullptr && piece->color() == current_color)
            {
                piece->move_to(move.dest);

                result = b.under_check(next_color(current_color))
                             ? MoveResult::Check
                             : MoveResult::Ok;

                current_color = next_color(current_color);
            }
            else
            {
                result = MoveResult::NotYourPiece;
            }
        }
        catch (std::out_of_range &)
        {
            result = MoveResult::NonExistentSquare;
        }
        catch (PieceException &e)
        {
            result = e.reason();
        }

        ui.submit(result);
    }
}
