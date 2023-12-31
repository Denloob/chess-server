#pragma once

#include "Client.h"
#include "Board.h"
#include "Pipe.h"
#include "Point.h"

class MagshimimUI : public Client
{
public:
    MagshimimUI(const Board &board);
    ~MagshimimUI();
    Move receive() override;
    void submit(MoveResult result) override;

private:
    Pipe _pipe;
};