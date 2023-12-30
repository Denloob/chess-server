#ifdef DPP

#include "DiscordGame.h"

DiscordGame::DiscordGame(dpp::snowflake white_id, dpp::snowflake black_id,
                         std::unique_ptr<Board> board)
    : _white_id(white_id), _black_id(black_id), _board(std::move(board))
{
}

dpp::snowflake DiscordGame::white_id() const
{
    return _white_id;
}

dpp::snowflake DiscordGame::black_id() const
{
    return _black_id;
}

UniqueMutexPtr<Board, std::timed_mutex> &DiscordGame::board()
{
    return _board;
}

#endif
