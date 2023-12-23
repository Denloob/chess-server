#pragma once
#include "King.h"
#include "Point.h"
#include "BoardConstants.h"
#include <iostream>
#include <array>
#include <memory>
#define DEFAULT_BOARD_STRING "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq"

class Board
{
public:
    explicit Board(const std::string &build_format_string = DEFAULT_BOARD_STRING);

    Board(const Board &) = delete;
    Board(Board &&) = delete;
    Board &operator=(const Board &) = delete;
    Board &operator=(Board &&) = delete;

    ~Board();

    /* @brief Simple getters for the piece * at the given possition */
    const Piece *at(const Point &pos) const;
    Piece *at(const Point &pos);

    std::unique_ptr<Piece> &operator[](const Point &pos);

    const King &king_of(Piece::Color color) const;
    King &king_of(Piece::Color color);

    bool under_check(Piece::Color color);

    std::string to_string() const;

private:
    const King *const &king_ptr_of(Piece::Color color) const;
    King *&king_ptr_of(Piece::Color color);


    King *_black_king{};
    King *_white_king{};
    BoardTable <std::unique_ptr<Piece>> _board{};
};
