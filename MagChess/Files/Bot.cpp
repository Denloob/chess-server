#include "Bot.h"
#include "DiscordGame.h"
#include <dpp/dpp.h>
#include <memory>

Bot::Bot(const std::string &token) : _cluster(token)
{
    _cluster.on_log(dpp::utility::cout_logger());
    _cluster.on_slashcommand(
        [this](const dpp::slashcommand_t &event)
        {
            if (event.command.get_command_name() == "challenge")
            {
                challenge(event);
            }
            else if (event.command.get_command_name() == "move")
            {
                move(event);
            }
        });
}

void Bot::register_commands()
{
    if (dpp::run_once<struct register_bot_commands>())
    {
        _cluster.global_bulk_command_create({
            dpp::slashcommand("challenge", "Challenge someone to a chess game",
                              _cluster.me.id)
                .add_option(dpp::command_option(dpp::co_user, "opponent",
                                                "The user to challenge", true))
                .add_option(
                    dpp::command_option(dpp::co_boolean, "random-color",
                                        "Randomly assign player colors")),
            dpp::slashcommand("move", "Make a move on a currently running game",
                              _cluster.me.id)
                .add_option(dpp::command_option(
                    dpp::co_string, "from", "The cell piece on which to move",
                    true))
                .add_option(dpp::command_option(dpp::co_string, "to",
                                                "Where to move to", true)),
        });
    }
}

void Bot::start()
{
    _cluster.start(dpp::st_wait);
}

void Bot::add_game(const dpp::snowflake &white, const dpp::snowflake &black)
{
    std::unique_lock games_lock(_games_mutex);

    auto game =
        std::make_shared<DiscordGame>(white, black, std::make_unique<Board>());

    _games.try_emplace(white, game);
    _games.try_emplace(black, game);
}

Client::MoveResult Bot::move(const dpp::snowflake &id, const Client::Move &move)
{
    std::shared_lock games_lock(_games_mutex);

    auto game = _games.at(id);
    std::unique_lock board_lock(game->board().mutex());
    Board *board = game->board().ptr();

    auto expected_id = board->current_color() == Piece::Color::White
                           ? game->white_id()
                           : game->black_id();
    if (id != expected_id)
    {
        throw not_your_move();
    }

    return board->do_move(move);
}

void Bot::remove_game(const dpp::snowflake &id)
{
    std::unique_lock games_lock(_games_mutex);

    std::shared_ptr<DiscordGame> game = _games.at(id);
    _games.erase(game->white_id());
    _games.erase(game->black_id());
}

std::string Bot::fen(const dpp::snowflake &id) const
{
    std::shared_lock games_lock(_games_mutex);

    auto game = _games.at(id);
    std::unique_lock board_lock(game->board().mutex());
    const Board *board = game->board().ptr();

    return board->to_fen_string();
}

Piece::Color Bot::current_color(const dpp::snowflake &id) const
{
    std::shared_lock games_lock(_games_mutex);

    auto game = _games.at(id);
    std::unique_lock board_lock(game->board().mutex());
    const Board *board = game->board().ptr();

    return board->current_color();
}

void Bot::set_color_information_on(dpp::embed &embed,
                                   const dpp::snowflake &id) const
{
    auto color = current_color(id);
    bool is_white = color == Piece::Color::White;

    namespace c = dpp::colors;

    embed.set_color(is_white ? c::white : c::black)
        .set_footer(dpp::embed_footer().set_text(
            std::string{is_white ? "White" : "Black"} + "'s move"));
}
