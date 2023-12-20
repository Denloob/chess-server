#pragma once

#include <array>

constexpr int BOARD_SIZE = 8;
template <typename T>
using BoardTable = std::array<std::array<T, BOARD_SIZE>, BOARD_SIZE>;
