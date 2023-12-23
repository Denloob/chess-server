#pragma once

#include "Point.h"

class Client
{
  public:
    enum class MoveResult
    {
        Ok,
        Check,
        NotYourPiece,
        DestinationOccupied,
        CheckOnSelf,
        NonExistentSquare,
        IllegalDestination,
        MoveToSelf,
        CheckMate,
    };

    struct Move
    {
        Point source;
        Point dest;
    };

    /**
     * @brief Receive a move from the client.
     *
     * @return Move from a source to a destination.
     */
    virtual Move receive() = 0;

    /**
     * @brief Submit the result code of the move to the client.
     *
     * @param result Result of the move.
     */
    virtual void submit(MoveResult result) = 0;

    /* Not movable, not copyable. */
    Client(const Client &) = delete;
    Client(Client &&) = delete;
    Client &operator=(const Client &) = delete;
    Client &operator=(Client &&) = delete;

    virtual ~Client() = 0;
};
