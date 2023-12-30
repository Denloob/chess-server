#include "Bot.h"
#include <dpp/dpp.h>
#include <string>

std::string get_bot_token()
{
    if (const char *env_token = std::getenv("BOT_TOKEN"))
    {
        return env_token;
    }

    std::string token;
    std::cin >> token;

    return token;
}

bool is_flag_present(int argc, char **argv, std::string_view flag)
{
    return std::any_of(argv + 1, argv + argc,
                       [&flag](std::string_view arg) { return arg == flag; });
}

int main(int argc, char **argv)
{
    Bot bot{get_bot_token()};

    if (is_flag_present(argc, argv, "--recreate-commands"))
    {
        bot.on_ready([&bot](const dpp::ready_t &) { bot.register_commands(); });
    }

    bot.start();
}
