#include "Bot.h"
#include "DiscordGame.h"
#include <dpp/appcommand.h>
#include <dpp/dpp.h>
#include <exception>
#include <memory>

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
