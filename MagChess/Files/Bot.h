#pragma once

#include "Board.h"
#include "Client.h"
#include "DiscordGame.h"
#include "UniqueMutexPtr.h"
#include <dpp/dpp.h>
#include <memory>
#include <string>
#include <unordered_map>

class Bot
{
  public:
    explicit Bot(const std::string &token);

    void register_commands();
    void start();

  private:
    void add_game(const dpp::snowflake &white, const dpp::snowflake &black);
    Client::MoveResult move(const dpp::snowflake &id, const Client::Move &move);
    void remove_game(const dpp::snowflake &id);

    dpp::cluster _cluster;
    std::unordered_map<dpp::snowflake, std::shared_ptr<DiscordGame>> _games{};
    mutable std::shared_timed_mutex _games_mutex{};
};
