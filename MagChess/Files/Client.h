#pragma once

#include "Point.h"

class Client
{
  public:
    enum class MoveResult : char
    {
        Ok = '0',
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

    virtual ~Client() = 0;
};

inline Client::~Client() = default;
