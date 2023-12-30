#include "Bot.h"
#include "DiscordGame.h"
#include "Point.h"
#include <dpp/dpp.h>
#include <memory>
#include <random>
#include <string>

constexpr const char *FEN_IMAGE_URL = "https://chessboardimage.com/";
constexpr const char *EMBED_IMAGE_URL_SUFFIX = ".png";

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

template <typename T, typename... Types>
std::optional<T> to_optional(const std::variant<Types...> &variant)
{
    if (std::holds_alternative<T>(variant))
    {
        return std::get<T>(variant);
    }

    return std::nullopt;
}

template <typename T>
std::optional<T> to_optional_from_event(const dpp::slashcommand_t &event,
                                        const std::string &parameter_name)
{
    return to_optional<T>(event.get_parameter(parameter_name));
}

/**
 * @brief Generate a random number using mt19937.
 *
 * @return A random number N in range first <= N <= last.
 */
unsigned long random_in_range(int first, int last)
{
    static std::random_device dev;
    static std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(first, last);

    return dist6(rng);
}

void Bot::challenge(const dpp::slashcommand_t &event)
{
    auto opponent = std::get<dpp::snowflake>(event.get_parameter("opponent"));
    bool random_color =
        to_optional_from_event<bool>(event, "random-color").value_or(false);

    auto white = event.command.usr.id;
    auto black = opponent;

    if (white == black)
    {
        event.reply(dpp::message("Can not challenge yourself.")
                        .set_flags(dpp::m_ephemeral));
        return;
    }

    {
        std::shared_lock games_lock(_games_mutex);
        bool opponent_playing = _games.find(black) != _games.end();
        bool self_playing = _games.find(white) != _games.end();
        if (opponent_playing || self_playing)
        {
            event.reply(
                dpp::message(
                    std::string{self_playing ? "You are" : "Your opponent is"} +
                    " currently playing with someone else.")
                    .set_flags(dpp::m_ephemeral));
            return;
        }
    }

    if (random_color && random_in_range(0, 1))
    {
        std::swap(white, black);
    }

    add_game(white, black);

    auto embed =
        dpp::embed()
            .set_description("<@!" + white.str() + "> (White) vs <@" +
                             black.str() + "> (Black)")
            .set_image(FEN_IMAGE_URL + fen(white) + EMBED_IMAGE_URL_SUFFIX);
    set_color_information_on(embed, white);

    event.reply(dpp::message(event.command.channel_id, embed)
                    .set_allowed_mentions({}, {}, {}, {}, {white, black}, {}));
}

/**
 * @brief Decode a move result into a human-readable string and game info.
 *
 * @param result The move result to decode.
 * @param from The source of the move whose result is being decoded.
 * @param to The destination of the move whose result is being decoded.
 * @param player The player whose move is being decoded.
 * @return Tuple of {message, is_valid_move, is_game_over}
 */
std::tuple<std::string, bool, bool>
decode_move_result(Client::MoveResult result, const std::string &from,
                   const std::string &to, dpp::snowflake player)
{
    switch (result)
    {
        using MR = Client::MoveResult;

        case MR::NotYourPiece:
            return {"There's no piece of your color on " + from, {}, {}};
        case MR::DestinationOccupied:
            return {"There's already a piece on " + to, {}, {}};
        case MR::CheckOnSelf:
            return {"This move leads to check on your king.", {}, {}};
        case MR::NonExistentSquare:
            return {"That's not a valid square.", {}, {}};
        case MR::IllegalDestination:
            return {"Illegal destination. That's not how this piece works.",
                    {},
                    {}};
        case MR::MoveToSelf:
            return {"You can't move to where you are.", {}, {}};
        case MR::Ok:
            return {"", true, {}};
        case MR::Check:
            return {"Check", true, {}};
        case MR::CheckMate:
            return {"Check and Mate. <@!" + player.str() + "> Won! 🎉🏆", true,
                    true};
    }
}

void Bot::move(const dpp::slashcommand_t &event)
{
    auto from = std::get<std::string>(event.get_parameter("from")).substr(0, 2);
    auto to = std::get<std::string>(event.get_parameter("to")).substr(0, 2);

    auto player = event.command.usr.id;

    Client::MoveResult result{};
    try
    {
        result = move(player, {to_point(from), to_point(to)});
    }
    catch (const not_your_move &e)
    {
        event.reply(dpp::message(event.command.channel_id, e.what())
                        .set_flags(dpp::m_ephemeral));
        return;
    }
    catch (const std::out_of_range &)
    {
        event.reply(dpp::message(event.command.channel_id,
                                 "There's no game currently running. Start one "
                                 "using `/challenge`")
                        .set_flags(dpp::m_ephemeral));
        return;
    }

    const auto [message_text, move_valid, game_over] =
        decode_move_result(result, from, to, player);

    dpp::message message;
    if (move_valid)
    {
        auto embed =
            dpp::embed()
                .set_image(FEN_IMAGE_URL + fen(player) + "-" + from + to +
                           EMBED_IMAGE_URL_SUFFIX)
                .set_description(from + " - " + to + "\n" + message_text);

        set_color_information_on(embed, player);

        message = dpp::message(event.command.channel_id, embed);
    }
    else
    {
        message = dpp::message(event.command.channel_id, message_text)
                      .set_flags(dpp::m_ephemeral);
    }

    if (game_over)
    {
        remove_game(player);
    }

    event.reply(message);
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
