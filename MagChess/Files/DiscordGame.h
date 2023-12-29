#pragma once

#include "Board.h"
#include "UniqueMutexPtr.h"
#include <dpp/snowflake.h>
#include <mutex>

class DiscordGame
{
  public:
    DiscordGame(dpp::snowflake white, dpp::snowflake black,
                std::unique_ptr<Board> board);

    dpp::snowflake white_id() const;
    dpp::snowflake black_id() const;
    UniqueMutexPtr<Board, std::timed_mutex> &board();

  private:
    dpp::snowflake _white_id{};
    dpp::snowflake _black_id{};
    UniqueMutexPtr<Board, std::timed_mutex> _board;
};
