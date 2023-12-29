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
