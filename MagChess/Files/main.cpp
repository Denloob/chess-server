#include "Board.h"
#include "Client.h"
#include "MagshimimUi.h"
#include <string>

int main()
{

    Board b;
    MagshimimUI ui{&b};

    while (true)
    {
        ui.submit(b.do_move(ui.receive()));
    }
}
