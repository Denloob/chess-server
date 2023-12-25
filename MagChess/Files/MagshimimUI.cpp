#include "MagshimimUi.h"
#include <cctype>
#include <limits>

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

Client::Move MagshimimUI::receive()
{
    std::string server_string = this->_pipe.getMessageFromGraphics();
    std::string first_half = server_string.substr(0, 2);
    std::string second_half = server_string.substr(2, 2);
    Point source(to_point(first_half));
    Point destination(to_point(second_half));
    return Client::Move{source, destination};
}
