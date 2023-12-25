#include "MagshimimUi.h"



MagshimimUI::MagshimimUI(Board* board)
{
    this->_pipe.connect();
    this->_pipe.sendMessageToGraphics(&(board->to_string() + "1\0")[0]);
}
MagshimimUI::~MagshimimUI()
{
    this->_pipe.close();
}

void MagshimimUI::submit(Client::MoveResult result)
{
    std::string send_msg{ static_cast<char> (result) };
    send_msg += '\0';
    this->_pipe.sendMessageToGraphics(&send_msg[0]);
}

Client::Move MagshimimUI::receive()
{
    std::string server_string = this->_pipe.getMessageFromGraphics(); 
    std::string first_half = server_string.substr(0, 1);
    std::string second_half = server_string.substr(2, 3);
    Point source(to_point(first_half));
    Point destination(to_point(second_half));
    return Client::Move{ source ,destination };
}

