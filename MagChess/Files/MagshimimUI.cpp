#ifdef _WIN32

#include "MagshimimUi.h"
#include <cctype>
#include <limits>
#include <fstream>

constexpr const char *GAME_LOG_PATH = "game_log.txt";

MagshimimUI::MagshimimUI(Board* board)
{
    bool try_again = true;
    while (!this->_pipe.connect() && try_again)
    {
        std::cout << "Connection failed. Try again? (y/n): ";
        char answ{};
        std::cin >> answ;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        try_again = std::tolower(answ) == 'y';
    }
    this->_pipe.sendMessageToGraphics(&(board->to_string() + "1\0")[0]);
}
MagshimimUI::~MagshimimUI()
{
    this->_pipe.close();
}

void MagshimimUI::submit(Client::MoveResult result)
{
    std::string send_msg{static_cast<char>(result)};
    send_msg += '\0';
    this->_pipe.sendMessageToGraphics(&send_msg[0]);
}

void append_log_line(const std::string &move)
{
    std::ofstream log_file(GAME_LOG_PATH, std::ios_base::app);
    if (!log_file.is_open())
    {
        std::cerr << "Failed to open output file for writing\n";
        return;
    }

    log_file << move << '\n';
}

Client::Move MagshimimUI::receive()
{
    std::string server_string = this->_pipe.getMessageFromGraphics();
    std::string first_half = server_string.substr(0, 2);
    std::string second_half = server_string.substr(2, 2);
    Point source(to_point(first_half));
    Point destination(to_point(second_half));
    return Client::Move{source, destination};
}

#endif
