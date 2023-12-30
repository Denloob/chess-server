#include <algorithm>
#include <iostream>
#include <string>

#ifdef WIN32
#include "MagshimimUi.h"
#endif

#ifdef DPP
#include "Bot.h"
#include <dpp/dpp.h>
#endif

bool is_flag_present(int argc, char **argv, std::string_view flag)
{
    return std::any_of(argv + 1, argv + argc,
                       [&flag](std::string_view arg) { return arg == flag; });
}

#ifdef DPP
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

int discord_main(int argc, char **argv)
{
    Bot bot{get_bot_token()};

    if (is_flag_present(argc, argv, "--recreate-commands"))
    {
        bot.on_ready([&bot](const dpp::ready_t &) { bot.register_commands(); });
    }

    bot.start();

    return 0;
}
#endif

#ifdef WIN32
int magshimim_main(int argc, char **argv)
{
    Board board;
    MagshimimUI ui{&board};

    while (true)
    {
        ui.submit(board.do_move(ui.receive()));
    }

    return 0;
}
#endif

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv)
{
    if (is_flag_present(argc, argv, "--discord"))
    {
#ifdef DPP
        return discord_main(argc, argv);
#else
        std::cerr << "Please install DPP and define the macro to use Discord Bot UI\n\n";
#endif
    }
    if (is_flag_present(argc, argv, "--magshimim"))
    {
#ifdef WIN32
        return magshimim_main(argc, argv);
#else
        std::cerr << "Magshimim UI is only supported on Windows.\n\n";
#endif
    }

    std::cerr << "No UI has been chosen. Please specify a UI.\n";
    std::cerr << "Usage: " << argv[0] << " (--discord|--magshimim)\n";

    return 1;
}
