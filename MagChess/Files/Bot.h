#pragma once

#include "Client.h"
#include "DiscordGame.h"
#include <dpp/dpp.h>
#include <exception>
#include <memory>
#include <string>
#include <unordered_map>

class Bot
{
  public:
    explicit Bot(const std::string &token);

    void register_commands();
    void start();

    template <typename F> void on_ready(F &&fun)
    {
        _cluster.on_ready(std::forward<F>(fun));
    };

  private:
    void add_game(const dpp::snowflake &white, const dpp::snowflake &black);
    Client::MoveResult move(const dpp::snowflake &id, const Client::Move &move);
    void remove_game(const dpp::snowflake &id);
    std::string fen(const dpp::snowflake &id) const;

    void set_color_information_on(dpp::embed &embed, const dpp::snowflake &id) const;

    Piece::Color current_color(const dpp::snowflake &id) const;

    void challenge(const dpp::slashcommand_t &event);
    void move(const dpp::slashcommand_t &event);
    void abort(const dpp::slashcommand_t &event);

    dpp::cluster _cluster;
    std::unordered_map<dpp::snowflake, std::shared_ptr<DiscordGame>> _games{};
    mutable std::shared_timed_mutex _games_mutex{};

    class not_your_move : public std::exception
    {
      public:
        const char *what() const noexcept override
        {
            return "It's currently not your move.";
        }
    };
};
